
// Application
#include "QMLFor.h"
#include "QMLComplexItem.h"

//-------------------------------------------------------------------------------------------------

QMLFor::QMLFor(const QPoint& pPosition, QMLItem* pInitialization, QMLItem* pCondition, QMLItem* pIncrementation, QMLItem* pContent)
    : QMLItem(pPosition)
    , m_pInitialization(pInitialization)
    , m_pCondition(pCondition)
    , m_pIncrementation(pIncrementation)
    , m_pContent(pContent)
{
}

//-------------------------------------------------------------------------------------------------

QMLFor::~QMLFor()
{
    if (m_pInitialization != nullptr)
        delete m_pInitialization;
    if (m_pCondition != nullptr)
        delete m_pCondition;
    if (m_pIncrementation != nullptr)
        delete m_pIncrementation;
    if (m_pContent != nullptr)
        delete m_pContent;
}

//-------------------------------------------------------------------------------------------------

QMLItem* QMLFor::initialization() const
{
    return m_pInitialization;
}

//-------------------------------------------------------------------------------------------------

QMLItem* QMLFor::condition() const
{
    return m_pCondition;
}

//-------------------------------------------------------------------------------------------------

QMLItem* QMLFor::incrementation() const
{
    return m_pIncrementation;
}

//-------------------------------------------------------------------------------------------------

QMLItem* QMLFor::content() const
{
    return m_pContent;
}

//-------------------------------------------------------------------------------------------------

QMap<QString, QMLItem*> QMLFor::members()
{
    QMap<QString, QMLItem*> vReturnValue;

    vReturnValue["initialization"] = m_pInitialization;
    vReturnValue["condition"] = m_pCondition;
    vReturnValue["incrementation"] = m_pIncrementation;
    vReturnValue["content"] = m_pContent;

    return vReturnValue;
}

//-------------------------------------------------------------------------------------------------

/*!
    Dumps the item to \a stream using \a iIdent for indentation. \br\br
    \a pContext is the context of this item. \br
    \a pParent is the caller of this method.
*/
void QMLFor::toQML(QTextStream& stream, QMLTreeContext* pContext, QMLItem* pParent, int iIdent)
{
    Q_UNUSED(pContext);
    Q_UNUSED(pParent);

    dumpNoIndentNoNewLine(stream, "for (");

    if (m_pInitialization != nullptr)
    {
        m_pInitialization->toQML(stream, pContext, this, iIdent + 1);
    }

    dumpNoIndentNoNewLine(stream, "; ");

    if (m_pCondition != nullptr)
    {
        m_pCondition->toQML(stream, pContext, this, iIdent + 1);
    }

    dumpNoIndentNoNewLine(stream, "; ");

    if (m_pIncrementation != nullptr)
    {
        m_pIncrementation->toQML(stream, pContext, this, iIdent + 1);
    }

    dumpNoIndentNoNewLine(stream, ")");
    dumpNewLine(stream);

    dumpIndented(stream, iIdent, "{");

    QMLComplexItem* pComplex = dynamic_cast<QMLComplexItem*>(m_pContent);

    if (pComplex != nullptr)
    {
        foreach (QMLItem* pItem, pComplex->contents())
        {
            if (pItem != nullptr)
            {
                dumpIndentedNoNewLine(stream, iIdent + 1, "");
                pItem->toQML(stream, pContext, this, iIdent + 1);
                dumpNewLine(stream);
            }
        }
    }
    else if (m_pContent != nullptr)
    {
        dumpIndentedNoNewLine(stream, iIdent + 1, "");
        m_pContent->toQML(stream, pContext, this, iIdent + 1);
        dumpNewLine(stream);
    }

    dumpIndented(stream, iIdent, "}");
}

//-------------------------------------------------------------------------------------------------

CXMLNode QMLFor::toXMLNode(CXMLNodableContext* pContext, CXMLNodable* pParent)
{
    CXMLNode xNode = QMLItem::toXMLNode(pContext, pParent);
    CXMLNode xInitialization("Initialization");
    CXMLNode xCondition("Condition");
    CXMLNode xIncrementation("Incrementation");
    CXMLNode xContent("Content");

    if (m_pInitialization != nullptr)
        xInitialization.nodes() << m_pInitialization->toXMLNode(pContext, this);

    if (m_pCondition != nullptr)
        xCondition.nodes() << m_pCondition->toXMLNode(pContext, this);

    if (m_pIncrementation != nullptr)
        xIncrementation.nodes() << m_pIncrementation->toXMLNode(pContext, this);

    if (m_pContent != nullptr)
        xContent.nodes() << m_pContent->toXMLNode(pContext, this);

    xNode.nodes() << xInitialization;
    xNode.nodes() << xCondition;
    xNode.nodes() << xIncrementation;
    xNode.nodes() << xContent;

    return xNode;
}
