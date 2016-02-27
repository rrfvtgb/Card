#include "commandhelper.h"
#include "helpcommand.h"

#include <QStringList>
#include <QVariant>

HelpCommand::HelpCommand(CommandHelper *commandholder)
    :Command(commandholder, "help"),
      _commandholder(commandholder)
{
    this->setDescription(tr("Obtain information about command <br><br> Usage: <b style='color:#C95;'>/help</b> [name]"));
}

QString HelpCommand::showPage(int i, int count)
{
    const QList<Command*> list = _commandholder->sortCommand();

    if(list.size() < (i-1)*count
            || i < 1){
        return tr("Invalid page number");
    }

    QString details = tr("--- Help [%1/%2] ---").arg(i).arg((list.size()+count-1)/count);

    int max = qMin(i*count, list.size());

    for(int j=(i-1)*count; j<max; j++){
        Command *cmd = list[j];
        details += "<br/> <b style='color:#C95;'>/"+cmd->name()
                +"</b> - "+this->shortDescription(cmd);
    }

    details +="</b>";

    return details;
}

QString HelpCommand::showCommand(QString name)
{
    QList<Command*> list = _commandholder->getCommandsByName(name);

    if(list.isEmpty()){
        return tr("No command found");
    }


    QString details = "Command by name ["+name+"]<br/>";

    foreach(Command* cmd, list){
        details += "<b style='color:#C95;'>/"+cmd->name()+"</b> - "+cmd->description()+"<br/>";
    }

    return details;
}

QVariant HelpCommand::execute(const QStringList &arg)
{
    if(arg.size() == 0){
        return this->showPage();
    }else if(arg.size() == 1){
        QString s = arg[0];

        bool isNum;
        int page = s.toInt(&isNum);

        if(isNum){
            return this->showPage(page);
        }else{
            return this->showCommand(s);
        }
    }

    return QVariant();
}

QString HelpCommand::shortDescription(Command *cmd)
{
    QString desc = cmd->description();

    int pos = desc.indexOf("<br");

    if(pos != -1){
        desc = desc.left(pos);
    }

    if(desc.size() > 50){
        pos = desc.indexOf(' ', 30);
        desc = desc.left(pos)+"...";
    }

    return desc;
}
