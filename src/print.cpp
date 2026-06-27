#include "../include/print.h"

void printMessage(vector<string> &msg)
{
    for (int i = 0; i < msg.size(); i ++){
        cout << msg[i] << " ";
    }
}
