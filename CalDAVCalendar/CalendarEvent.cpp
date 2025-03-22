/*********************************************//*!@addtogroup file Files*//*@{*/
/*!
 *******************************************************************************
* File identification:      $Id: CalendarEvent.cpp 11 2017-01-16 20:27:13Z cypax $
* Revision of last commit:  $Rev: 11 $
* Author of last commit:    $Author: cypax $
* Date of last commit:      $Date: 2017-01-16 21:27:13 +0100 (Mo, 16 Jan 2017) $
 *******************************************************************************
 *
 * @file          CalendarEvent.cpp
 * @author        Cypax (cypax.net)
 *
 * @brief         Implementation file of class CalendarEvent.
 */
/************************************************************************//*@}*/

/******************************************************************************/
/* Library includes                                                           */
/******************************************************************************/
#include <QDebug>
#include <QColor>

/******************************************************************************/
/* Own includes                                                               */
/******************************************************************************/
#include "CalendarEvent.h"

/******************************************************************************/
/* Namespace                                                                 */
/******************************************************************************/

/******************************************************************************/
/* Constants (#define)                                                        */
/***************************************//*!@addtogroup define Constants*//*@{*/
/***** End of: define Constants *****************************************//*@}*/

/******************************************************************************/
/* Constructors                                                               */
/**********************************//*!@addtogroup constrc Constructors *//*@{*/

CalendarEvent::CalendarEvent(QObject *parent) : QObject(parent)
{
  m_calendarName    = "unnamed";
  m_Name            = "";
  m_Location        = "";
  m_Description     = "";
  m_StartDateTime   = QDateTime();
  m_EndDateTime     = QDateTime();
  m_Categories      = "";
  m_Exdates         = "";
  m_RRULE           = "";
  m_Color           = QColor(qrand() & 0xFF, qrand() & 0xFF, qrand() & 0xFF).name();
  m_IsCanceled      = false;
  m_UID             = "";
  m_HREF            = "";
  m_CalendarPointer = NULL;
}

CalendarEvent::CalendarEvent(const CalendarEvent& other) : QObject()
{
  copyFrom(other);
}

/***** End of: constrc Constructors *************************************//*@}*/

/******************************************************************************/
/* Deconstructor                                                              */
/******************************//*!@addtogroup deconstrc Deconstructors *//*@{*/
/***** End of: deconstrc Constructors ***********************************//*@}*/

/******************************************************************************/
/* Public functions                                                           */
/*****************************//*!@addtogroup pubfunct Public functions *//*@{*/

CalendarEvent& CalendarEvent::operator=(const CalendarEvent& other)
{
  copyFrom(other);
  return (*this);
}

bool CalendarEvent::operator<(const CalendarEvent& other) const
{
  return (this->m_StartDateTime < other.m_StartDateTime);
}

void CalendarEvent::copyFrom(const CalendarEvent& other)
{
  setColor(other.m_Color);
  setCalendarName(other.m_calendarName);
  setName(other.m_Name);
  setLocation(other.m_Location);
  setDescription(other.m_Description);
  setStartDateTime(other.m_StartDateTime);
  setEndDateTime(other.m_EndDateTime);
  setCategories(other.m_Categories);
  setExdates(other.m_Exdates);
  setRRULE(other.m_RRULE);
  setIsCanceled(other.m_IsCanceled);
  setUID(other.m_UID);
  setHREF(other.m_HREF);
  setCalendarPointer(other.m_CalendarPointer);
  setParent(other.parent());
}

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

QString CalendarEvent::getColor(void) const
{
  return m_Color;
}

void CalendarEvent::setColor(const QString& color)
{
  if (color != m_Color)
  {
    m_Color = color;
    emit colorChanged(m_Color);
  }
}

QString CalendarEvent::calendarName() const
{
  return m_calendarName;
}

void CalendarEvent::setCalendarName(const QString &calendarName)
{
  if (calendarName != m_calendarName)
  {
    m_calendarName = calendarName;
    emit calendarNameChanged(m_calendarName);
  }
}


QString CalendarEvent::name() const
{
  return m_Name;
}


void CalendarEvent::setName(const QString &name)
{
  if (name != m_Name)
  {
    m_Name = name;
    emit nameChanged(m_Name);
  }
}

void CalendarEvent::setCalendarPointer(QObject* ptr)
{
  m_CalendarPointer = ptr;
}

QObject* CalendarEvent::getCalendarPointer(void) const
{
  return m_CalendarPointer;
}


QString CalendarEvent::location() const
{
  return m_Location;
}

void CalendarEvent::setLocation(const QString& location)
{
  if (location != m_Location)
  {
    m_Location = location;
    emit locationChanged(m_Location);
  }
}


QString CalendarEvent::description() const
{
  return m_Description;
}

void CalendarEvent::setDescription(const QString& description)
{
  if (description != m_Description)
  {
    m_Description = description;
    emit descriptionChanged(m_Description);
  }
}


QDateTime CalendarEvent::getStartDateTime(void) const
{
    return m_StartDateTime;
}

void CalendarEvent::setStartDateTime(const QDateTime &startDateTime)
{
  if (startDateTime != m_StartDateTime)
  {
    m_StartDateTime = startDateTime;
    emit startDateTimeChanged(m_StartDateTime);
  }
}


QDateTime CalendarEvent::getEndDateTime(void) const
{
  return m_EndDateTime;
}

void CalendarEvent::setEndDateTime(const QDateTime &endDateTime)
{
  if (endDateTime != m_EndDateTime)
  {
    m_EndDateTime = endDateTime;
    emit endDateTimeChanged(m_EndDateTime);
  }
}


QString CalendarEvent::getRRULE() const
{
  return m_RRULE;
}

void CalendarEvent::setRRULE(const QString& rrule)
{
  if (m_RRULE != rrule)
  {
    m_RRULE = rrule;
    emit rruleChanged(m_RRULE);
  }
}


QString CalendarEvent::getExdates() const
{
  return m_Exdates;
}

void CalendarEvent::setExdates(const QString& exdates)
{
  if (m_Exdates != exdates)
  {
    m_Exdates = exdates;
    emit exdatesChanged(m_Exdates);
  }
}


QString CalendarEvent::getCategories() const
{
  return m_Categories;
}

void CalendarEvent::setCategories(const QString& categories)
{
  if (m_Categories != categories)
  {
    m_Categories = categories;
    emit categoriesChanged(m_Categories);
  }
}


bool CalendarEvent::getIsCanceled() const
{
  return m_IsCanceled;
}

void CalendarEvent::setIsCanceled(const bool& isCanceled)
{
  if (m_IsCanceled != isCanceled)
  {
    m_IsCanceled = isCanceled;
    emit isCanceledChanged(m_IsCanceled);
  }
}

QString CalendarEvent::getUID(void) const
{
  return m_UID;
}


QString CalendarEvent::getHREF(void) const
{
  return m_HREF;
}


void CalendarEvent::setUID(const QString& uid)
{
  if (uid != m_UID)
  {
    m_UID = uid;
    emit uidChanged(m_UID);
  }
}


void CalendarEvent::setHREF(const QString& href)
{
  if (href != m_HREF)
  {
    m_HREF = href;
    emit hrefChanged(m_HREF);
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
