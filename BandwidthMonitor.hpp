class BandwidthMonitor {
public:
    BandwidthMonitor(pcap_if_t* device);

    // to be run in a seperate thread for each BandwidthMonitor
    void run();

private:
    // saves Bytes and Time to a file, along with a usage statistic 
    void save_snapshot() const;
    void update_snapshot(std::chrono::seconds& acc_time);

private:
    // static so multiple instances accumulate to same variable
    static unsigned long long Bytes;
    static std::chrono::seconds Time;
    static std::mutex Mutex;

    // used for saving snapshots of the accumulated values
    // after a certain time period
    std::chrono::system_clock::time_point m_time_point;
    std::chrono::seconds m_snapshot_time { 30 };
    const std::string bytefile { "bytes.txt" };
    const std::string timefile { "time.txt" };

    // so run() can open the pcap_of for the device
    pcap_if_t* m_device;
    // the pcap_if used to track bandwidth usage
    PcapAdapter m_adapter;
};
