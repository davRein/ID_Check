#ifndef JSONFILENAMES_H
#define JSONFILENAMES_H

#include <QString>

class JsonFilenames
{
public:
    JsonFilenames();

    QString getFn_ID_0_Send() const;
    QString getFn_ID_0_Receive() const;
    QString getFn_ID_1_Send() const;
    QString getFn_ID_1_Receive() const;

private:
    void initFilenames();

    const QString fn_ID_0_Send = "use_iocontrol.json";
    const QString fn_ID_0_Receive = "id_0_result_ok.json";
    const QString fn_ID_1_Send = "id_1_setOutput.json";
    const QString fn_ID_1_Receive = "id_1_result_true.json";


};

#endif // JSONFILENAMES_H
