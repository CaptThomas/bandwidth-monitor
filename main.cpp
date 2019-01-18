PcapDevices d;
auto alldevs = d.get_devices();

std::vector<BandwidthMonitor> monitors;
for (const auto& d : alldevs) {
    if (!d->flags & PCAP_IF_LOOPBACK) {
        monitors.emplace_back(d);
    }
}

// thread for each device which will open a pcap_if to track bandwidth usage
std::vector<std::thread> monitor_threads;
for (const auto& m : monitors) {
    monitor_threads.emplace_back(&BandwidthMonitor::run, m);
}

for (auto& t : monitor_threads) {
    t.join();
}
