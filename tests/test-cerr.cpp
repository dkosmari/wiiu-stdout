#include <iostream>

#include <sysapp/launch.h>
#include <vpad/input.h>
#include <whb/proc.h>

using std::cout;
using std::cerr;
using std::endl;


int main()
{
    cout << "Hello world!" << endl;
    cerr << "This is an ERROR message!" << endl;
    cout << "Press any button to quit." << endl;

    WHBProcInit();
    while (WHBProcIsRunning()) {
        VPADStatus vpad;
        int r = VPADRead(VPAD_CHAN_0, &vpad, 1, nullptr);
        if (r == 1)
            if (vpad.trigger) {
                cout << "Button press detected!" << endl;
                SYSLaunchMenu();
            }
    }
    WHBProcShutdown();
}
