#include "check_uii.h"

//! [Check_UII] default contructor
Check_UII::Check_UII()
{

}
//! [Check_UII]

//! [checkTransponderID] Checks the value of the transponder ID
//! n < 1000: green
//! 1000 < n < 2000: yellow
//! n >= 2000 or wrong input: red
QString Check_UII::checkTransponderID(int nUII){
    if(nUII < 1000){
        return "green";
    } else if(nUII >= 1000 && nUII < 2000){
        return "yellow";
    } else {
        return "red";
    }
}

//! [checkTransponderID]


