<!--
GS
Jan. 2023

This is the start of my answer to this question:
https://stackoverflow.com/questions/15958056/how-to-use-sublime-over-ssh

I really need to finish my investigations and then write a nice answer and get this working!
I really like the `subl` tool here, too: https://stackoverflow.com/a/18538531/4561887


References:
1. Google search for "sublime text over ssh": https://www.google.com/search?q=sublime+text+over+ssh&sxsrf=AJOqlzUl9x54LoHAUcRyy-eNJNqg0lMS0Q:1673998920848&ei=SDLHY6e4M7LK9AP14L64Cw&ved=0ahUKEwin_J_448_8AhUyJX0KHXWwD7cQ4dUDCBA&uact=5&oq=sublime+text+over+ssh&gs_lcp=Cgxnd3Mtd2l6LXNlcnAQAzIECAAQRzIECAAQRzIECAAQRzIECAAQRzIECAAQRzIECAAQRzIECAAQRzIECAAQRzoKCAAQRxDWBBCwA0oECEEYAEoECEYYAFCTBViTBWCPBmgBcAJ4AIABAIgBAJIBAJgBAKABAcgBCMABAQ&sclient=gws-wiz-serp&sec_act=d
1. https://stackoverflow.com/questions/15958056/how-to-use-sublime-over-ssh

-->


**Huge** limitations:
1. You cannot open full directories or projects in Sublime--only individual files. 
1. It works in only 1-direction. So, if you modify the file via the ssh session on the remote machine (including with [`git checkout -- path/to/file`](https://stackoverflow.com/a/65258783/4561887) to restore it), the change does *not* show up in your local Sublime Text editor. 
    1. This is *un*like if you were editing the file purely locally in multiple editors at once. If you edited the file and saved in some other editor, Eclipse would detect that the file changed and instantly reload it.

I consider these two limitations big enough that I'm going to probably move to Microsoft VSCode instead (unfortunately), since it natively supports full-featured editing and workflows over ssh.



mkdir -p ~/bin
curl -Lo ~/bin/rmate https://raw.githubusercontent.com/textmate/rmate/master/bin/rmate
chmod a+x ~/bin/rmate
sudo apt install ruby
. ~/.profile

$ rmate --version
rmate version 1.5.10 (2021-04-26)





3rd-party shell script replacement: https://github.com/aurora/rmate



sudo wget -O /usr/local/bin/subl https://raw.github.com/aurora/rmate/master/rmate; sudo chmod +x /usr/local/bin/subl
$ subl --version
rmate-sh 1.0.2 (2019-04-08)


