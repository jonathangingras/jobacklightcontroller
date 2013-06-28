jobacklightcontroller
=====================

Simple Qt gui allowing easy backlight controlling on intel_backlight linux interface. 
ie. /sys/class/backlight/intel_backlight/brightness
<p>
This gui's first goal is not portability but it might work on other backlight interface. In order to do so,
you may change lines defining the backlight path and backlight_max path at the beginning of "main.cpp". ie.
</p>
<code>
  #define MAX_B get_back_int("/sys/class/backlight/intel_backlight/max_brightness")<br>
  #define PATH "/sys/class/backlight/intel_backlight/brightness"<br>
</code>
<p>
In order to make the programm work, you need to change the permissions of your backlight interface to 
allow your user to write the file "brightness". This must be redone each boot time. My own solution
is a multi-user deamon I enable at boot (I run systemd).
</p>

<h3>INSTALL</h3>
<p>
$ qmake-qt4 # or whatever your qmake command looks like<br>
$ make<br>
$ mv jobacklightcontroller /usr/bin # or wherever in your environnement PATH<br>
</p>
