# TimerLib
This is a nonportable high resolution timer library for Lua on Windows by creating a binding to the Windows Performance Counters API. 

It is capable of having multiple timers running simultaneously. 

This project is formatted as a Visual Studio solution. Upon building it creates a DLL that can be loaded by Lua. 
You will want to place this DLL in your `package.cpath`. 

You will then load it in Lua like so: 

    timerlib = require("TimerLib")

Functions:

<h1>timerlib.Create(resolution)</h1>


Creates and returns a `TimerLibTimer`. The timer is not running when created.

`resolution` is how many decimal places the timer's time is rounded to. 

Examples:

    timerlib.Create(1) -- Creates a timer that rounds to one decimal place, e.g., 2.2. 
    timerlib.Create(3) -- Creates a timer that rounds to three decimal places, e.g., 2.203. 

<h1>timerlib.start(timer)</h1>

Starts the timer `timer`. 
    
Can also be invoked via:
    
    timer:start()

<h1>timerlib.stop(timer)</h1>

Stops the timer `timer`. 
    
Can also be invoked via:
    
    timer:stop()

<h1>timerlib.reset(timer)</h1> 

Stops the timer `timer` and sets it's internal clock that is obtained with `timerlib.getcount` back to zero. 
    
Can also be invoked via:
    
    timer:reset()
    
<h1>timerlib.getcount(timer)</h1>

Returns the total time elapsed for a specific timer in seconds and rounded to the precision set in `timerlib.Create`.

Can also be invoked via:
    timer:getcount()
