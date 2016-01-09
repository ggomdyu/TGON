#──────────────────────────────────────#


ReadMe : TGON_Core.Platform - Created by 차준호 in 01/08/2016


※ Utility & Misc
Include PlatformXXX.h. This include Headers for your platform automatically.


※ Main
This project has a platform dependenced main, and it call pseudo main function that custumized by user.
User should implement it that named <tgMain>.


※  Window
Include "PlatformWindow.h" header.
And make window through using 'tgon::Window' type which declared by typedef.
This requires WindowStyle. It has many information:  size, position, ...
 

#──────────────────────────────────────#