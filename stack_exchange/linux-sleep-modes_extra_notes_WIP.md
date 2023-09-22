Linux sleep notes

https://www.kernel.org/doc/Documentation/power/states.txt

https://blog.wirelessmoves.com/2022/11/running-ubuntu-linux-on-bleeding-edge-hardware-dell-notebook-with-an-intel-12800h-and-an-nvidia-gpu.html

> One touchy point when it comes to Linux and notebook support is if suspend and resume works and which flavor is supported by the hardware. It looks like the Dell 5570 only supports suspend to idle (s2idle), but power consumption is only around 1 watt. That’s much better than the HP notebook I bought last year, which draws 4 watts while being suspended. Together with the 86 Wh battery, that’s something I can live with, even though I would have preferred the ‘deep’ sleep suspend variant with an even further reduced power consumption at the expense of a slightly longer wake-up time. But it’s working, so I won’t complain.



https://www.google.com/search?q=dell+precision+%225570%22+won%27t+%22suspend%22+in+%22Ubuntu%22&sxsrf=APwXEdcAEbdSwk6x0dRnsaeQAhKdh8jkjw%3A1686543460020&ei=ZJyGZJhin-eQ8g_4hIPABA&ved=0ahUKEwiYpNT-77z_AhWfM0QIHXjCAEgQ4dUDCBA&uact=5&oq=dell+precision+%225570%22+won%27t+%22suspend%22+in+%22Ubuntu%22&gs_lcp=Cgxnd3Mtd2l6LXNlcnAQAzIFCCEQoAEyBQghEKABMgUIIRCgATIFCCEQqwI6CggAEEcQ1gQQsAM6BQgAEKIESgQIQRgAUKQHWJYcYKyUAWgBcAF4AIABlAGIAbgCkgEDMi4xmAEAoAEBwAEByAEI&sclient=gws-wiz-serp

grep '' /sys/power/*

```bash
/sys/power$ grep '' /sys/power/*
/sys/power/disk:[platform] shutdown reboot suspend test_resume 
/sys/power/image_size:26782547968
/sys/power/mem_sleep:[s2idle]
/sys/power/pm_async:1
/sys/power/pm_debug_messages:0
/sys/power/pm_freeze_timeout:20000
/sys/power/pm_print_times:0
/sys/power/pm_test:[none] core processors platform devices freezer
/sys/power/pm_trace:0
/sys/power/pm_trace_dev_match:msr
/sys/power/pm_trace_dev_match:
/sys/power/pm_trace_dev_match:clockevents
/sys/power/pm_wakeup_irq:1
/sys/power/reserved_size:1048576
/sys/power/resume:0:0
/sys/power/resume_offset:0
/sys/power/state:freeze mem disk
grep: /sys/power/suspend_stats: Is a directory
/sys/power/sync_on_suspend:1
/sys/power/wake_lock:
/sys/power/wake_unlock:
/sys/power/wakeup_count:8456

```


https://gist.github.com/bmcbm/375f14eaa17f88756b4bdbbebbcfd029?permalink_comment_id=4184379#gistcomment-4184379


https://askubuntu.com/questions/1455199/entire-battery-drains-even-though-s2idle-deep-is-available-in-my-sys-power


```
sudo journalctl

Jun 11 21:16:08 gabriel-Precision-5570 systemd[1]: Starting System Suspend...
Jun 11 21:16:08 gabriel-Precision-5570 systemd-sleep[7202]: Entering sleep state 'suspend'...
Jun 11 21:16:08 gabriel-Precision-5570 kernel: PM: suspend entry (s2idle)
Jun 11 21:16:08 gabriel-Precision-5570 kernel: Filesystems sync: 0.005 seconds
Jun 11 21:16:14 gabriel-Precision-5570 kernel: Freezing user space processes ... (elapsed 0.001 seconds) done.
Jun 11 21:16:14 gabriel-Precision-5570 kernel: OOM killer disabled.
Jun 11 21:16:14 gabriel-Precision-5570 kernel: Freezing remaining freezable tasks ... (elapsed 0.001 seconds) done.
Jun 11 21:16:14 gabriel-Precision-5570 kernel: printk: Suspending console(s) (use no_console_suspend to debug)
Jun 11 21:16:14 gabriel-Precision-5570 kernel: ACPI: EC: interrupt blocked
Jun 11 21:16:14 gabriel-Precision-5570 kernel: ACPI: EC: interrupt unblocked
Jun 11 21:16:14 gabriel-Precision-5570 kernel: i915 0000:00:02.0: [drm] GuC firmware i915/adlp_guc_70.1.1.bin version 70.1
Jun 11 21:16:14 gabriel-Precision-5570 kernel: i915 0000:00:02.0: [drm] HuC firmware i915/tgl_huc_7.9.3.bin version 7.9
Jun 11 21:16:14 gabriel-Precision-5570 kernel: i915 0000:00:02.0: [drm] HuC authenticated
Jun 11 21:16:14 gabriel-Precision-5570 kernel: i915 0000:00:02.0: [drm] GuC submission enabled
Jun 11 21:16:14 gabriel-Precision-5570 kernel: i915 0000:00:02.0: [drm] GuC SLPC enabled
Jun 11 21:16:14 gabriel-Precision-5570 kernel: i915 0000:00:02.0: [drm] GuC RC: enabled
Jun 11 21:16:14 gabriel-Precision-5570 kernel: ucsi_acpi USBC000:00: failed to re-enable notifications (-110)
Jun 11 21:16:14 gabriel-Precision-5570 kernel: OOM killer enabled.
Jun 11 21:16:14 gabriel-Precision-5570 kernel: Restarting tasks ... 
Jun 11 21:16:14 gabriel-Precision-5570 kernel: mei_hdcp 0000:00:16.0-b638ab7e-94e2-4ea2-a552-d1c54b627f04: bound 0000:00:02.0 (ops i915_hdcp_component_ops [i915])
Jun 11 21:16:14 gabriel-Precision-5570 kernel: mei_pxp 0000:00:16.0-fbf6fcf1-96cf-4e2e-a6a6-1bab8cbe36b1: bound 0000:00:02.0 (ops i915_pxp_tee_component_ops [i915])
Jun 11 21:16:14 gabriel-Precision-5570 kernel: done.
Jun 11 21:16:14 gabriel-Precision-5570 systemd-resolved[1198]: Clock change detected. Flushing caches.
Jun 11 21:16:14 gabriel-Precision-5570 systemd[1]: NetworkManager-dispatcher.service: Deactivated successfully.
Jun 11 21:16:14 gabriel-Precision-5570 kernel: thermal thermal_zone13: failed to read out thermal zone (-61)
Jun 11 21:16:14 gabriel-Precision-5570 systemd-sleep[7202]: System returned from sleep state.
Jun 11 21:16:14 gabriel-Precision-5570 bluetoothd[1310]: Controller resume with wake event 0x0
Jun 11 21:16:14 gabriel-Precision-5570 kernel: PM: suspend exit
Jun 11 21:16:15 gabriel-Precision-5570 gdm3[1585]: GLib: Source ID 94 was not found when attempting to remove it
Jun 11 21:16:15 gabriel-Precision-5570 systemd[1]: systemd-suspend.service: Deactivated successfully.
Jun 11 21:16:15 gabriel-Precision-5570 systemd[1]: Finished System Suspend.
Jun 11 21:16:15 gabriel-Precision-5570 systemd[1]: Stopped target Sleep.
Jun 11 21:16:15 gabriel-Precision-5570 systemd[1]: Reached target Suspend.

```

https://askubuntu.com/questions/1455199/entire-battery-drains-even-though-s2idle-deep-is-available-in-my-sys-power#comment2575794_1455363

https://learnubuntumate.weebly.com/draining-battery.html


to my surprise, the RAID to AHCI change in the BIOS (and that change alone) actually fixed the battery drain. I measured over 20 hours of sleep, occasionally waking it up to check the battery percentage, and it drained only 7% during 20.5 hrs. Out of the box and installing Fedora 34, it used to drain 5% every hour. To compare apples to apples, it’s an hourly sleep consumption rate of 5% (RAID) vs. 0.3% (AHCI).
https://discussion.fedoraproject.org/t/dell-battery-drained-while-suspended/66514/10


```bash
echo 's2idle' | sudo tee -a /sys/power/mem_sleep
cat /sys/power/mem_sleep

# https://learnubuntumate.weebly.com/draining-battery.html
sudo journalctl | grep "PM: suspend" | tail -2
```

https://askubuntu.com/q/1434729/327339


Let's change BIOS from RAID to AHCI or whatever, to try to improve sleep efficiency!
(do experiments later)

Also search the BIOS for wake on keypress options.
