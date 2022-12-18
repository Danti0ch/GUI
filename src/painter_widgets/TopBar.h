#ifndef TOP_BAR_H
#define TOP_BAR_H

#include "BarWidget.h"
#include "Settings.h"

// TODO: implement like list of droplists
class TopBar : public hBarWidget{
public:
    TopBar();
    ~TopBar() = default;
};

class FileDropList : public VListWidget{
public:
    FileDropList();
    ~FileDropList() = default;
};

void openFile();
void saveFile(const std::string& name);

#endif // TOP_BAR_H
