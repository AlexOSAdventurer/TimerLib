# TimerLib
This is a nonportable high resolution timer library for Lua on Windows by creating a binding to the Windows Performance Counters API. 

It is capable of having multiple timers running simultaneously. 

This project is formatted as a Visual Studio solution. Upon building it creates a DLL that can be loaded by Lua. 
You will want to place this DLL in your `package.cpath`. 

You will then load it in Lua like so: 

    timerlib = require("TimerLib")

<h1>Functions</h1>

<h2>timerlib.Create(resolution)</h2>


Creates and returns a `TimerLibTimer`. The timer is not running when created.

`resolution` is how many decimal places the timer's time is rounded to. 

Examples:

    timerlib.Create(1) -- Creates a timer that rounds to one decimal place, e.g., 2.2. 
    timerlib.Create(3) -- Creates a timer that rounds to three decimal places, e.g., 2.203. 

<h2>timerlib.start(timer)</h2>

Starts the timer `timer`. 
    
Can also be invoked via:
    
    timer:start()

<h2>timerlib.stop(timer)</h2>

Stops the timer `timer`. 
    
Can also be invoked via:
    
    timer:stop()

<h2>timerlib.reset(timer)</h2> 

Stops the timer `timer` and sets it's internal clock that is obtained with `timerlib.getcount` back to zero. 
    
Can also be invoked via:
    
    timer:reset()
    
<h2>timerlib.getcount(timer)</h2>

Returns the total time elapsed for a specific timer in seconds and rounded to the precision set in `timerlib.Create`.

Can also be invoked via:

    timer:getcount()
