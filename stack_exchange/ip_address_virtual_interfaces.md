<!--
GS
2020~2023

https://unix.stackexchange.com/a/593142/114401
-->

_Tested on Ubuntu 18.04 and 22.04._


## 1. The basics

1. **Create a virtual (dummy) adapter/interface device**
    ```bash
    # 1. Install the "dummy" socket interface Linux kernel module.
    sudo modprobe dummy

    # 2. Ensure the "dummy" Linux kernel module is installed.
    sudo lsmod | grep dummy

    # 3. View all existing socket interfaces/adapters, whether WiFi, Ethernet,
    # or virtual (dummy)
    ip address
    ip a  # or (short version of the command above)

    # 4. Create a virtual (dummy) interface named `eth_dummy`.
    sudo ip link add eth_dummy type dummy

    # 5. View it. You'll now see "eth_dummy" as one of your attached interfaces.
    ip address

    # 6. Add an IP address and netmask to this new dummy interface. Use any IP
    # address and netmask you like. Ex: `10.0.0.1/24` in this case. 
    # - Note that the `/24` means that the first (most-significant, or
    #   left-most) 24 bits of the 32-bit netmask will be set to 1's. This
    #   (`/24`) is the same as `255.255.255.0`. See below for details and a
    #   full list of possible netmasks.
    # - See `ip address help` for command syntax help. 
    sudo ip address add 10.0.0.1/24 dev eth_dummy

    # 7. See the newly-created device and the IP address you just
    # assigned to it.
    ip address
    ```

    That's it!

1. **Add IP addresses to your interface:** 

    You can add as many IP addresses as you want to your network interface. 

    In case you are using sockets to receive from (bind to, and receive on) many different IP addresses at once, you can easily add them all to this one dummy interface. 

    Here, I am adding two more IP addresses and netmasks as I see fit:
    ```bash
    sudo ip address add 192.168.2.1/24 dev eth_dummy
    sudo ip address add 10.5.4.1/8 dev eth_dummy
    ```

    `ip address` now shows the following for my `eth_dummy` virtual (`type dummy`) interface. So, I can have my C, C++, Python, etc. sockets bind to IP addresses `10.0.0.1`, `192.168.2.1`, and `10.5.4.1` on this interface. This is great for airplane travel when you need to test your network and simulated output packets without having a real network switch plugged into your computer (I'm on an airplane now as I write this. Pretty sure that puts me in the "mile high" coding club). 
    ```bash
    10: eth_dummy: <BROADCAST,NOARP> mtu 1500 qdisc noop state DOWN group default qlen 1000
        link/ether 4a:e7:bc:8f:2e:2d brd ff:ff:ff:ff:ff:ff
        inet 10.0.0.1/24 scope global eth_dummy
           valid_lft forever preferred_lft forever
        inet 192.168.2.1/24 scope global eth_dummy
           valid_lft forever preferred_lft forever
        inet 10.5.4.1/8 scope global eth_dummy
           valid_lft forever preferred_lft forever
    ```

1. **Delete or update existing IP addresses on your interface:**

    To change an existing IP address on your interface, you must delete and re-add it. The `ip address change` command is something else entirely--[it changes flags/configuration parameters on an existing IP address](https://serverfault.com/a/666521/357116). So, delete and re-add an IP address on your interface like this:
    ```bash
    # general form
    sudo ip address del <current_ip_address> dev <interface_device_name>
    sudo ip address add <new_ip_address> dev <interface_device_name>

    # Example: change `10.5.4.1/8` above to `32.42.52.62/28`
    sudo ip address del 10.5.4.1/8 dev eth_dummy
    sudo ip address add 32.42.52.62/28 dev eth_dummy

    # verify the change
    ip address
    ```

1. **Delete the entire dummy interface device:**
    ```bash
    # 1. Delete this `eth_dummy` dummy device you created.
    sudo ip link delete eth_dummy

    # 2. Ensure 'eth_dummy' is deleted and doesn't show up here now.
    ip address
    ```

Done!

To learn more about the `ip address add` and `ip address change` type commands, see:
1. `ip address help`, as well as: 
1. This answer here: [Server Fault: understanding "ip addr change" and "ip addr replace" commands](https://serverfault.com/a/666521/357116). 


## Details


## 2. Non-standard forms

I have observed, [as has @Martin on ServerFault](https://serverfault.com/q/476926/357116), that:

> If I execute `ip addr change 10.11.12.6/24 dev eth0` or `ip addr replace 10.11.12.6/24 dev eth0` then `10.11.12.6` is just added to `eth0`.

This is also the case with `ip addr add 10.11.12.6/24 dev eth0`. 

So, you can also *add* a new IP address to your interface using `ip address change` or `ip address replace` instead of `ip address add`. Don't do that, however. That's just confusing. The `add` command is intended to *add* a new IP address, and the `change` command is intended to *change* config flags in an existing IP address. Note that `change` does *not* update nor change the IP address itself. To do that, use `del` to delete an existing IP address first, and then `add` to add a new one. Nobody really seems to know what `replace` is for or how it's different from `change`. The source code holds the answer I suppose. 

So these technically all do the same thing:
```bash
# add IP address 10.11.12.6/24
sudo ip address add 10.11.12.6/24 dev eth_dummy     # standard way to add this IP (recommended)
sudo ip address change 10.11.12.6/24 dev eth_dummy  # non-standard way to add this IP
sudo ip address replace 10.11.12.6/24 dev eth_dummy # non-standard way to add this IP
```

And you can also put the IP address at the end of the command too, but that's also a non-standard form. `ip address help` shows the IP (as `IFADDR`, or "interface address") coming *before* the word `dev`. So, here are the alternative forms:
```bash
sudo ip address add 10.11.12.6/24 dev eth_dummy     # standard way to add this IP (recommended)
sudo ip address add dev eth_dummy 10.11.12.6/24     # non-standard way to add this IP
```

And you don't have to type out the whole word `address`. The `ip` command is smart enough that once it sees some of the `address` argument, it accepts it, since no other argument to `ip` in this position begins with `a`. So, these all work:
```bash
sudo ip address add 10.11.12.6/24 dev eth_dummy  # standard form
# "short", non-standard forms:
sudo ip addres add 10.11.12.6/24 dev eth_dummy
sudo ip addre add 10.11.12.6/24 dev eth_dummy
sudo ip addr add 10.11.12.6/24 dev eth_dummy
sudo ip add add 10.11.12.6/24 dev eth_dummy  # yeah that's confusing: `add add...`
sudo ip ad add 10.11.12.6/24 dev eth_dummy
sudo ip a add 10.11.12.6/24 dev eth_dummy
```

Lastly, don't forget the `/number` part at the end to specify the netmask. Consider the following:
```bash
# This:
sudo ip address add 10.11.12.6 dev eth_dummy
# Defaults to this, which isn't very useful
sudo ip address add 10.11.12.6/32 dev eth_dummy

# So, remember to specify your own useful netmask, such as 
# `/24` (255.255.255.0), instead, like this:
sudo ip address add 10.11.12.6/24 dev eth_dummy
```


## 3. Netmasks

Here is a full list of possible netmasks when setting the IP address and netmask as `ip/netmask`, such as `10.0.0.1/24`. The `/24` here means that the first (most-significant, or left-most) 24 bits of the 32-bit netmask will be set to `1`s. Netmask `/24` is the same as `255.255.255.0`. 

Here is a full list of possible netmasks:

Whole-byte netmasks:
```
/32 = 255.255.255.255
/24 = 255.255.255.0     # <== most common
/16 = 255.255.0.0
/8  = 255.0.0.0
/0  = 0.0.0.0           # (I don't even know if this is a valid option)
```

All netmasks:
```
/32 = 255.255.255.255
/31 = 255.255.255.254
/30 = 255.255.255.252
/29 = 255.255.255.248
/28 = 255.255.255.240
/27 = 255.255.255.224
/26 = 255.255.255.192
/25 = 255.255.255.128
/24 = 255.255.255.0     # <== most common
/23 = 255.255.254.0
/22 = 255.255.252.0
/21 = 255.255.248.0
/20 = 255.255.240.0
/19 = 255.255.224.0
/18 = 255.255.192.0
/17 = 255.255.128.0
/16 = 255.255.0.0
/15 = 255.254.0.0
/14 = 255.252.0.0
/13 = 255.248.0.0
/12 = 255.240.0.0
/11 = 255.224.0.0
/10 = 255.192.0.0
/9 = 255.128.0.0
/8 = 255.0.0.0
/7 = 254.0.0.0
/6 = 252.0.0.0
/5 = 248.0.0.0
/4 = 240.0.0.0
/3 = 224.0.0.0
/2 = 192.0.0.0
/1 = 128.0.0.0
/0 = 0.0.0.0            # (I don't even know if this is a valid option)
```


## 4. More details

`lsmod` shows "the status of modules in the Linux Kernel" (see `man lsmod`). Try it out! Just type in
```bash
lsmod
```

One of the modules is called `dummy`. Let's look to see it's there:
```bash
$ lsmod | grep dummy
dummy                  16384  0
```

Yep, it's there. Good. That Linux kernel module _must_ be present for you to be able to run the `sudo ip link add eth_dummy type dummy` command above to create the virtual interface using the `dummy` kernel module. If you don't have it, see [@slm's answer][1]. 

Before you create a new virtual interface, run this to see what IP addresses and interfaces you already have:
```bash
ip address
```

You can also take a look at this:
```bash
ifconfig
```

After you have created your new virtual interface, you will see it in the output of the `ip address` command above. Note: `ifconfig` may not show a virtual, dummy device you create, but `ip address` will.

----

Wait, but my coworker ran `sudo ip addr change 10.0.0.1 dev eth_dummy`, in place of `sudo ip address change 10.0.0.1 dev eth_dummy` (notice `addr` in place of `address`). Or, maybe they ran `sudo ip a change 10.0.0.1 dev eth_dummy` (notice `a` in place of `address`). What's up with that!?

Well, this particular command only needs enough of its characters to ensure it knows what you mean. In other words, _once you have enough characters in the command for it to know you couldn't possibly mean any other command, it accepts it._ Since no other subcommand after `ip` starts with the letter `a`, `ip a` is enough. Therefore, all of the below commands are equivalent:
```bash
ip address
ip addres
ip addre
ip addr
ip add
ip ad
ip a
```

Just be aware of this weird sort of thing when sharing information and looking at the `help` menus and `man` pages (shown in my references below). Otherwise, you'll be all sorts of confused, like I was, when no matter how hard you search you can't find the `a` (as in `ip a`) or `addr` (as in `ip addr`) commands listed anywhere in these page. Just realize both of those are short for `address`. Ah...now _there it is_ in the help pages!
```bash
$ ip help
Usage: ip [ OPTIONS ] OBJECT { COMMAND | help }
       ip [ -force ] -batch filename
where  OBJECT := { link | address | addrlabel | route | rule | neigh | ntable |
                   tunnel | tuntap | maddress | mroute | mrule | monitor | xfrm |
                   netns | l2tp | fou | macsec | tcp_metrics | token | netconf | ila |
                   vrf | sr }
       OPTIONS := { -V[ersion] | -s[tatistics] | -d[etails] | -r[esolve] |
                    -h[uman-readable] | -iec |
                    -f[amily] { inet | inet6 | ipx | dnet | mpls | bridge | link } |
                    -4 | -6 | -I | -D | -B | -0 |
                    -l[oops] { maximum-addr-flush-attempts } | -br[ief] |
                    -o[neline] | -t[imestamp] | -ts[hort] | -b[atch] [filename] |
                    -rc[vbuf] [size] | -n[etns] name | -a[ll] | -c[olor]}
                    ```

And you can run `ip address help` (or `man ip address`), _to see the existence of the `ip address add` and `ip address change` commands!_:
```bash
$ ip address help
Usage: ip address {add|change|replace} IFADDR dev IFNAME [ LIFETIME ]
                                                      [ CONFFLAG-LIST ]
       ip address del IFADDR dev IFNAME [mngtmpaddr]
       ip address {save|flush} [ dev IFNAME ] [ scope SCOPE-ID ]
                            [ to PREFIX ] [ FLAG-LIST ] [ label LABEL ] [up]
       ip address [ show [ dev IFNAME ] [ scope SCOPE-ID ] [ master DEVICE ]
                         [ type TYPE ] [ to PREFIX ] [ FLAG-LIST ]
                         [ label LABEL ] [up] [ vrf NAME ] ]
       ip address {showdump|restore}
IFADDR := PREFIX | ADDR peer PREFIX
          [ broadcast ADDR ] [ anycast ADDR ]
          [ label IFNAME ] [ scope SCOPE-ID ]
SCOPE-ID := [ host | link | global | NUMBER ]
FLAG-LIST := [ FLAG-LIST ] FLAG
FLAG  := [ permanent | dynamic | secondary | primary |
           [-]tentative | [-]deprecated | [-]dadfailed | temporary |
           CONFFLAG-LIST ]
CONFFLAG-LIST := [ CONFFLAG-LIST ] CONFFLAG
CONFFLAG  := [ home | nodad | mngtmpaddr | noprefixroute | autojoin ]
LIFETIME := [ valid_lft LFT ] [ preferred_lft LFT ]
LFT := forever | SECONDS
TYPE := { vlan | veth | vcan | vxcan | dummy | ifb | macvlan | macvtap |
          bridge | bond | ipoib | ip6tnl | ipip | sit | vxlan | lowpan |
          gre | gretap | erspan | ip6gre | ip6gretap | ip6erspan | vti |
          nlmon | can | bond_slave | ipvlan | geneve | bridge_slave |
          hsr | macsec
```


## References
1. [@slm's answer here][1] 
1. `ip help`
1. `man ip`
1. `ip link help`
1. `man ip link`
1. `ip address help`
1. `man ip address`
1. [Server Fault: understanding "ip addr change" and "ip addr replace" commands](https://serverfault.com/a/666521/357116) - very useful to understand the difference between `ip address add`, `ip address change`, and `ip address replace`, as well as `ip address del`.


## Related
1. [my answer] [AskUbuntu: How to enable/disable networking (ethernet or wifi) devices, arbitrarily](https://askubuntu.com/questions/168032/how-to-disable-built-in-wifi-and-use-only-usb-wifi-card/1320155#1320155)



  [1]: https://unix.stackexchange.com/a/152334/114401
