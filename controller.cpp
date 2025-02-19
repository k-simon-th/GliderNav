#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    tasksList = new TasksList(this);
    logList = new FlightLogList(this);

    QDir baseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if(!baseDir.exists()) baseDir.mkpath("./");

    QDir aptDir = QDir(baseDir.filePath("apt"));
    if(!aptDir.exists()) aptDir.mkpath("./");
    airportModel = new AirportModel(this);
    airportModel->importAirportsFromDir(aptDir);

    QDir asDir = QDir(baseDir.filePath("as"));
    if(!asDir.exists()) asDir.mkpath("./");
    airspaceModel = new AirspaceModel(this);
    airspaceModel->importAirspacesFromDir(asDir);


    airportFilterModel = new AirportFilterModel(this);
    airportFilterModel->setSourceModel(airportModel);

    airspaceFilterModel = new AirspaceFilterModel(this);
    airspaceFilterModel->setSourceModel(airspaceModel);
}

Task *Controller::getCurrentTask() const
{
    return currentTask;
}

void Controller::setCurrentTask(Task *newCurrentTask)
{
    if (currentTask == newCurrentTask)
        return;
    currentTask = newCurrentTask;
    emit currentTaskChanged();
}

TasksList *Controller::getTasksList() const
{
    return tasksList;
}

FlightLog *Controller::getCurrentLog() const
{
    return currentLog;
}

void Controller::setCurrentLog(FlightLog *newCurrentLog)
{
    if (currentLog == newCurrentLog)
        return;
    currentLog = newCurrentLog;
    emit currentLogChanged();
}

FlightLogList *Controller::getLogList() const
{
    return logList;
}

AirportModel *Controller::getAirportModel() const
{
    return airportModel;
}

AirspaceModel *Controller::getAirspaceModel() const
{
    return airspaceModel;
}

AirportFilterModel *Controller::getAirportFilterModel() const
{
    return airportFilterModel;
}

AirspaceFilterModel *Controller::getAirspaceFilterModel() const
{
    return airspaceFilterModel;
}
