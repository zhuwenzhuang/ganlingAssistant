#include"structs.h"
void speak(QString str){
    {
    QFile file("tmp.vbs");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        exit(-1);
        return;
    }
    QTextStream out(&file);
    out << "CreateObject(\"SAPI.SpVoice\").Speak "<<"\""<<str<<"\""<<endl;
    }
    QProcess::startDetached("C:/windows/system32/wscript.exe "
    "tmp.vbs");
}
