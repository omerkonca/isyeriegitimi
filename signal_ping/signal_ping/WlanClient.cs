using Wlan;

internal class WlanClient
{
    public WlanClient()
    {
    }

    public object Interfaces { get; internal set; }

    internal class WlanInterface
    {
        internal WlanAvailableNetwork[] GetAvailableNetworkList(int v)
        {
            throw new NotImplementedException();
        }
    }
}