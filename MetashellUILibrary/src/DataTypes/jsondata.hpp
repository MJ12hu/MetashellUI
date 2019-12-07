#ifndef JSONDATA_H
#define JSONDATA_H
#include <QString>

struct JsonData
{
    JsonData()
    {
        sourceRow = sourceColumn = instantiationRow = instantiationColumn =
                    timeTaken = timeTakenRatio = depth = children = -1;
    }

    QString     type;

    //all
    QString     name;
    QString     sourceFileName;
    int         sourceRow;
    int         sourceColumn;
    QString     instantiationFileName;
    int         instantiationRow;
    int         instantiationColumn;

    //optional
    QString     kind;
    double      timeTaken;
    double      timeTakenRatio;

    //call_graph
    int         depth;
    int         children;

    bool operator<(const JsonData& p_other) const
    {
        return timeTaken < p_other.timeTaken;
    }
};

typedef QVector<JsonData> JsonArray;

#endif // JSONDATA_H
