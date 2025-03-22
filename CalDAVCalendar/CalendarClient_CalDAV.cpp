/*********************************************//*!@addtogroup file Files*//*@{*/
/*!
 *******************************************************************************
* File identification:      $Id: CalendarClient_CalDAV.cpp 18 2017-01-26 17:33:06Z cypax $
* Revision of last commit:  $Rev: 18 $
* Author of last commit:    $Author: cypax $
* Date of last commit:      $Date: 2017-01-26 18:33:06 +0100 (Do, 26 Jan 2017) $
 *******************************************************************************
 *
 * @file          CalendarClient_CalDAV.cpp
 * @author        Cypax (cypax.net)
 *
 * @brief         Implementation file of class CalendarClient_CalDAV.
 */
/************************************************************************//*@}*/

/******************************************************************************/
/* Library includes                                                           */
/******************************************************************************/
#include <QDebug>

/******************************************************************************/
/* Own includes                                                               */
/******************************************************************************/
#include "CalendarClient_CalDAV.h"
#include "CalendarEvent.h"

/******************************************************************************/
/* Namespace                                                                 */
/******************************************************************************/

/******************************************************************************/
/* Constants (#define)                                                        */
/***************************************//*!@addtogroup define Constants*//*@{*/

#define DEBUG_CALENDARCLIENT_CALDAV 0
#if DEBUG_CALENDARCLIENT_CALDAV
#define QDEBUG qDebug()
#else
#define QDEBUG if (0) qDebug()
#endif

/***** End of: define Constants *****************************************//*@}*/

/******************************************************************************/
/* Constructors                                                               */
/**********************************//*!@addtogroup constrc Constructors *//*@{*/
CalendarClient_CalDAV::CalendarClient_CalDAV(QObject* parent) : CalendarClient(parent)
{
  m_CalendarType = E_CALENDAR_CALDAV;
  m_DataStream = NULL;
  m_pUploadReply = NULL;

  m_Username = "";
  m_Password = "";
  m_HostURL = "";
  m_syncToken = "";
  m_DisplayName = "";
  m_cTag = "";
  m_Year = 1;
  m_Month = 1;
  m_YearToBeRequested = QDate::currentDate().year();;
  m_MonthToBeRequested = QDate::currentDate().month();
  lastSyncYear = -1;
  lastSyncMonth = -1;
  m_bRecoveredFromError = false;

  setupStateMachine();
}

/***** End of: constrc Constructors *************************************//*@}*/

/******************************************************************************/
/* Deconstructor                                                              */
/******************************//*!@addtogroup deconstrc Deconstructors *//*@{*/
CalendarClient_CalDAV::~CalendarClient_CalDAV()
{
  m_SynchronizationTimer.stop();
}

/***** End of: deconstrc Constructors ***********************************//*@}*/

/******************************************************************************/
/* Public functions                                                           */
/*****************************//*!@addtogroup pubfunct Public functions *//*@{*/
/***** End of: pubfunct Public functions ********************************//*@}*/

/******************************************************************************/
/* Protected functions                                                        */
/*************************//*!@addtogroup protfunct Protected functions *//*@{*/
/***** End of: protfunct Protected functions ****************************//*@}*/

/******************************************************************************/
/* Private functions                                                          */
/*************************//*!@addtogroup privfunct Private functions   *//*@{*/
/***** End of: privfunct Private functions ******************************//*@}*/

/******************************************************************************/
/* Public slots                                                               */
/*************************//*!@addtogroup pubslots Public slots         *//*@{*/

int CalendarClient_CalDAV::getYear() const
{
  return m_Year;
}


int CalendarClient_CalDAV::getMonth() const
{
  return m_Month;
}

void CalendarClient_CalDAV::setUsername(const QString username)
{
  m_Username = username;
  emit usernameChanged(m_Username);
}

QString CalendarClient_CalDAV::getUsername(void) const
{
  return m_Username;
}

void CalendarClient_CalDAV::setPassword(const QString password)
{
  m_Password = password;
  emit passwordChanged(m_Password);
}

QString CalendarClient_CalDAV::getPassword(void) const
{
  return m_Password;
}

void CalendarClient_CalDAV::startSynchronization(void)
{
  QDEBUG << m_DisplayName << ": " << "!!!forcing synchronization!!!";
  emit forceSynchronization();
}


void CalendarClient_CalDAV::stopSynchronization(void)
{
}

void CalendarClient_CalDAV::recover(void)
{
  QDEBUG << m_DisplayName << ": " << "trying to recover from EEROR state";
  m_bRecoveredFromError = true;
  emit recoverSignal();
}

void CalendarClient_CalDAV::setYear(const int& year)
{
  if (E_STATE_IDLE == m_State)
  {
    if (m_Year != year)
    {
      QDEBUG << m_DisplayName << ": " << "Year changed from" << m_Year << "to" << year;
      m_Year = year;
      emit yearChanged(m_Year);
      m_YearToBeRequested = year;
      startSynchronization();
    }
  }
  else
  {
    QDEBUG << m_DisplayName << ": " << "requested Year changed from" << m_YearToBeRequested << "to" << year;
    m_YearToBeRequested = year;
  }
}

void CalendarClient_CalDAV::setMonth(const int& month)
{
  if (E_STATE_IDLE == m_State)
  {
    if (m_Month != month)
    {
      QDEBUG << m_DisplayName << ": " << "Month changed from" << m_Month << "to" << month;
      m_Month = month;
      emit monthChanged(m_Month);
      m_MonthToBeRequested = month;
      startSynchronization();
    }
  }
  else
  {
    QDEBUG << m_DisplayName << ": " << "requested Month changed from" << m_MonthToBeRequested << "to" << month;
    m_MonthToBeRequested = month;
  }
}


void CalendarClient_CalDAV::handleUploadHTTPError(void)
{
  m_UploadRequestTimeoutTimer.stop();
  if (NULL != m_pUploadReply)
  {
    QDEBUG << m_DisplayName << ": " << "HTTP upload error:" << m_pUploadReply->errorString();
    emit error(m_pUploadReply->errorString());
  }
  else
  {
    QDEBUG << m_DisplayName << ": " << "ERROR: Invalid reply pointer when handling HTTP error.";
    emit error("Invalid reply pointer when handling HTTP error.");
  }

}

void CalendarClient_CalDAV::handleUploadFinished(void)
{
  m_UploadRequestTimeoutTimer.stop();

  QDEBUG << m_DisplayName << ": " << "HTTP upload finished";

  if (NULL != m_pUploadReply)
  {
    QDEBUG << m_DisplayName << ": " << "received:\r\n" << m_pUploadReply->readAll();
    emit forceSynchronization();
  }
}


/***** End of: pubslots Public slots ************************************//*@}*/

/******************************************************************************/
/* Protected slots                                                            */
/*********************//*!@addtogroup protslots Protected slots         *//*@{*/
/***** End of: protslots Protected slots ********************************//*@}*/

/******************************************************************************/
/* Private slots                                                              */
/*************************//*!@addtogroup privslots Private slots       *//*@{*/
/***** End of:privslots Private slots ***********************************//*@}*/

/**** Last line of source code                                             ****/
