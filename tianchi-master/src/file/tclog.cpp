#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>

#include <tianchi/file/tclog.h>

///**
// * @brief Tianchi::Log 全局 Log4Qt 实例，可在应用程序中直接使用。
// */
//Log4Qt Log;
void TcLog::setAppFile(const QString& AppFile)
{
    QFileInfo fi(AppFile);
    QString logFile = fi.absolutePath() + QDir::separator() + fi.baseName() + ".log";

    setLogFile(logFile);
}

void TcLog::setLogFile(const QString& LogFile)
{
    init();
    m_FileName = LogFile;
}

void TcLog::setLogLevel(int level)
{
    m_level = level;
}

void TcLog::error(const QString &S, const QString &SourceName, int SourceLine)
{
    if(m_level >= LOG_ERROR)
    {
       this->write(S, LOG_ERROR, SourceName, SourceLine);
    }
}

void TcLog::warning(const QString &S, const QString &SourceName, int SourceLine)
{
    if(m_level >= LOG_WARNING)
    {
       this->write(S, LOG_WARNING, SourceName, SourceLine);
    }
}

void TcLog::track(const QString &S, const QString &SourceName, int SourceLine)
{
    if(m_level >= LOG_TRACK)
    {
       this->write(S, LOG_TRACK, SourceName, SourceLine);
    }
}

void TcLog::info(const QString &S, const QString &SourceName, int SourceLine)
{
    if(m_level >= LOG_INFO)
    {
       this->write(S, LOG_INFO, SourceName, SourceLine);
    }
}

void TcLog::debug(const QString &S, const QString &SourceName, int SourceLine)
{
    if(m_level >= LOG_DEBUG)
    {
       this->write(S, LOG_DEBUG, SourceName, SourceLine);
    }
}

void TcLog::init()
{
    m_mapLevel[LOG_ERROR]   = QString("Error  ");
    m_mapLevel[LOG_WARNING] = QString("Warning");
    m_mapLevel[LOG_TRACK]   = QString("Track  ");
    m_mapLevel[LOG_INFO]    = QString("Info   ");
    m_mapLevel[LOG_DEBUG]   = QString("Debug  ");

    setLogLevel(LOG_DEBUG);
}

void TcLog::write(const QString& S, int level, const QString& SourceName, int SourceLine)
{
    if (!m_FileName.isEmpty())
    {
        QFileInfo fi(m_FileName);
        QFile f(m_FileName);
        QDir dir(fi.absoluteDir());

        if (!dir.exists())
        {
            dir.mkpath(fi.absolutePath());
        }

        if (dir.exists() && f.open(QFile::Text | QFile::Append))
        {
            QString line = m_mapLevel[level];
            line.append("\t");
            line.append(S);

            if (!SourceName.isEmpty())
            {
                line.append("\t");
                line.append(SourceName);
                if (SourceLine > 0)
                {
                    line.append(":");
                    line.append(QString::number(SourceLine));
                }
            }
            QTextStream out(&f);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz")
                << "\t" << line.trimmed() <<endl;

            f.close();
        }
    }
}
