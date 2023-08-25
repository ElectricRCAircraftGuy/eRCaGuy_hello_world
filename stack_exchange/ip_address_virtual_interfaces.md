<!--
GS
2020~2023

https://unix.stackexchange.com/a/593142/114401
-->

_Tested on Ubuntu 18.04 and 22.04._


## 1. The basics

1. Create a virtual (dummy) adapter/interface
    ```bash
    # 1. Install the "dummy" socket interface Linux kernel module.
    sudo modprobe dummy

    # 2. Ensure the "dummy" Linux kernel module is installed.
    sudo lsmod | grep dummy

    # 3. View all existing socket interfaces/adapters, whether WiFi, Ethernet, or
    # virtual (dummy)
    ip address
    ip a  # or (short version of the command above)

    # 4. Create a virtual (dummy) interface named `eth_dummy`.
    sudo ip link add eth_dummy type dummy

    # 5. View it. You'll now see "eth_dummy" as one of your attached interfaces.
    ip address

    # 6. Change this new interface's IP address to whatever you like: 
    # Ex: `10.0.0.1/24` in this case. 
    #
    # - Note that the `/24` means that the first 24 bits of the 32-bit netmask will
    #   be set to 1's. This is the same as `255.255.255.0`. 
    #
    #   Netmask options may include:
    #   
    #       # whole-bytes:
    #       /32 = 255.255.255.255
    #       /24 = 255.255.255.0   <== most common
    #       /16 = 255.255.0.0
    #       /8  = 255.0.0.0
    #       /0  = 0.0.0.0  - (I don't even know if this is a valid option)
    #       
    #       # others:
    #       /32 = 255.255.255.255
    #       /31 = 255.255.255.254
    #       /30 = 255.255.255.252
    #       /29 = 255.255.255.248
    #       /28 = 255.255.255.240
    #       /27 = 255.255.255.224
    #       /26 = 255.255.255.192
    #       /25 = 255.255.255.128
    #       /24 = 255.255.255.0
    #       /23 = 255.255.254.0
    #       /22 = 255.255.252.0
    #       /21 = 255.255.248.0
    #       /20 = 255.255.240.0
    #       etc. etc. 
    #
    sudo ip address change dev eth_dummy 10.0.0.1/24

    # 7. See the newly-created device and the IP address you just
    # assigned to it.
    ip address
    ```

    That's it!

1. To delete this dummy interface:
    ```bash
    # 1. Delete this `eth_dummy` dummy device you created.
    sudo ip link delete eth_dummy type dummy

    # 2. Ensure 'eth_dummy' is deleted and doesn't show up here now.
    ip address
    ```

Done!


## 2. More details

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

Wait, but my coworker ran `sudo ip addr change dev eth_dummy 10.0.0.1`, in place of `sudo ip address change dev eth_dummy 10.0.0.1` (notice `addr` in place of `address`). Or, maybe they ran `sudo ip a change dev eth_dummy 10.0.0.1` (notice `a` in place of `address`). What's up with that!?

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

And `ip address help` (or `man ip address`), _to see the existence of the `ip address change` command!_:
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


## Related
1. [my answer] [AskUbuntu: How to enable/disable networking (ethernet or wifi) devices, arbitrarily](https://askubuntu.com/questions/168032/how-to-disable-built-in-wifi-and-use-only-usb-wifi-card/1320155#1320155)



  [1]: https://unix.stackexchange.com/a/152334/114401
