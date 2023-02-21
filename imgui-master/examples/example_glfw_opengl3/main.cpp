
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include "implot.cpp"
#include "implot.h"
#include "implot_demo.cpp"
#include "implot_internal.h"
#include "implot_items.cpp"




#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
   

    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = NULL;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(500, 500));

  /*
    if (ImGui::Begin("hesap makinesi")) {

            ImGui::SetCursorPos(ImVec2(50, 50));
            if (ImGui::Button("1", ImVec2(40, 40)))
            {

            }
            ImGui::SetCursorPos(ImVec2(100, 50));
            if (ImGui::Button("2", ImVec2(40, 40)))
            {

            }
            ImGui::SetCursorPos(ImVec2(150, 50));
            if (ImGui::Button("3", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(50, 100));
            if (ImGui::Button("4", ImVec2(40, 40)))
            {

            }
            ImGui::SetCursorPos(ImVec2(100, 100));
            if (ImGui::Button("5", ImVec2(40, 40)))
            {

            }
            ImGui::SetCursorPos(ImVec2(150, 100));
            if (ImGui::Button("6", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(50, 150));
            if (ImGui::Button("7", ImVec2(40, 40)))
            {

            }
            ImGui::SetCursorPos(ImVec2(100, 150));
            if (ImGui::Button("8", ImVec2(40, 40)))
            {

            }
            ImGui::SetCursorPos(ImVec2(150, 150));
            if (ImGui::Button("9", ImVec2(40, 40)))
            {

            }


            ImGui::SetCursorPos(ImVec2(50, 200));
            if (ImGui::Button("0", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(100, 200));
            if (ImGui::Button(".", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(150,200));
            if (ImGui::Button("=", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(200,50));
            if (ImGui::Button("*", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(200, 100));
            if (ImGui::Button("/", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(200, 150));
            if (ImGui::Button("-", ImVec2(40, 40)))
            {

            }


            ImGui::SetCursorPos(ImVec2(200, 200));
            if (ImGui::Button("+", ImVec2(40, 40)))
            {

            }

            ImGui::SetCursorPos(ImVec2(50,250));
            if (ImGui::Button("sonuc", ImVec2(190, 190)))
            {

            }

        }ImGui::End();
  */      

        int bar_data[10]= { 0,1,2,3,4,5,6,7,8,9 };
        float x_data[13]= { 0.1,1.1,2.1,3.2,4.2,5.2,6.6,7.3,8.2,9.2,4.3,5.2,8.5 };
        float y_data[13]= { 0.1,1.1,2.1,3.2,4.2,5.2,6.6,7.3,8.2,9.2,4.3,5.2,8.5 };


        ImGui::Begin("deneme");
        if (ImPlot::BeginPlot("my plot"))
        {
            ImPlot::PlotBars("my bar plot", bar_data, 11);
            ImPlot::PlotLine("my line plot", x_data,y_data, 13);
            
            ImPlot::EndPlot();
        }
        ImGui::End();

            

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
