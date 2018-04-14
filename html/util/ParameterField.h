//
// Created by christ on 14.04.18.
//

#ifndef SHEEPNDOGS_PARAMETERFIELD_H
#define SHEEPNDOGS_PARAMETERFIELD_H


#include <Wt/WLineEdit.h>
#include <Wt/WContainerWidget.h>

class ParameterField : public Wt::WLineEdit
{
public:
    ParameterField( const std::string &name, double &parameter, Wt::WContainerWidget &container,
                    bool isInline = false );
    
    void connect();

private:
    std::string name;
    double* parameter;
    Wt::WLineEdit* widget;
    
};


#endif //SHEEPNDOGS_PARAMETERFIELD_H
