#include "QKeyPushButton.h"
#include "widgetKeyBoard.h"
#include <QKeyEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QDebug>
#include <QApplication>


QKeyPushButton::QKeyPushButton(QWidget *parent) :
    QPushButton(parent),
    m_parent(parent)

{

	this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON));
    
	connect(this, SIGNAL(pressedKey(bool)), SLOT(getKeyPress(bool)));
    if ((static_cast<widgetKeyBoard *> (parent))->isEmbeddedKeyboard() == true)
    this->style_embedded = QString(EMBEDDED_KEYBOARD);
}


void QKeyPushButton::getKeyPress(bool capsStatus)
{
	int 		keyCode = 0;
	QKeyEvent	*key = NULL;
	QString		text = this->text();
    text.replace("&&", "&"); // for the & key we need to use the && so when writing into the LineEdit remove one &

    // for all special key except CAPS (RETURN, ALT, SHIFT, etc ...) shall forward to the widgetKeyBoard component:
    if (NO_SPECIAL_KEY(text) == false && (IS_BACK(text) == true || IS_BACK_EMB(text) == true || IS_TAB(text) == true ||
                                         IS_RETURN(text) == true || IS_CTRL_LEFT(text) == true ||
                                         IS_ALT(text) == true || IS_CANC(text) == true || IS_CUT_LEFT(text) == true ||
                                         IS_PASSWORD(text) || IS_PASSWORD_EMB(text) || IS_PASTE(text) || IS_COPY(text))){
        
        //qDebug() << "big if condition ";
		key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
        //qDebug() << "big if condition 2";
    }else{ // these are printable characters
        keyCode = text.toUtf8()[0]; // takes the numeric value (always uppercase)
        if (capsStatus == false)    // if it must be lowercase, check if the character is alphabetic
        {
            text = text.toLower();
            
            // now also change the shown key on the keyboard e.g. a instead of A
            qDebug() << "lower case: Pressed Key: " << text; // text can be letters or special character
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::NoModifier, text);
		}
		else
            key = new QKeyEvent(QEvent::KeyPress, keyCode, Qt::ShiftModifier, text);
            qDebug() << "upper case: Pressed Key: " << text;
	}
        if(IS_RETURN(text)==true)
        {   // todo BOMKE: implement action if return key is pressed
            qDebug() << "return key pressed";
            //emit returnKeyPressed();
            qDebug() << "return key pressed 2";

        }

    ((widgetKeyBoard *) this->m_parent)->receiptChildKey(key, NULL);
	QCoreApplication::processEvents();
}


void QKeyPushButton::mousePressEvent(QMouseEvent *)
{
    static bool             m_capsActive = true;
    widgetKeyBoard          *tmpKeyBoard = (widgetKeyBoard *)this->m_parent;
    QString                 text = this->text();
    QString                 defaultStyleButton = QString(DEFAULT_STYLE_BUTTON);
    QString                 changedColorButton = QString(CHANGED_BACKGROUND_BUTTON);
	//
    // if it is the uppercase:
    if (IS_CAPS(text) == true)
    {
        
        if (m_capsActive == false){
			m_capsActive = true;
            qDebug() << "enable CapsLock: m_capsActive = " << m_capsActive;
            // if the capslock button is pressed, change layout from e.g. 'a' to 'A' and vise versa
            tmpKeyBoard->toggleCapsLock();
            // visual feedback for CAPS key itself
            
        }else{
            changedColorButton = QString(FUNCTIONAL_BUTTON_STYLE); // DEFAULT_BACKGROUND_BUTTON
            
			m_capsActive = false;
            qDebug() << "disable capslock";
            tmpKeyBoard->toggleCapsLock();



		}
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
	}
    else if (tmpKeyBoard->isEnabledSwitchingEcho() == true && (IS_PASSWORD(text) == true || IS_PASSWORD_EMB(text) == true))
        tmpKeyBoard->switchKeyEchoMode(tmpKeyBoard->currentTextBox());
    else{ // color while key is pressed
        
        this->setStyleSheet(defaultStyleButton + changedColorButton + this->style_embedded);
		this->repaint();
		QCoreApplication::processEvents();
		emit pressedKey(m_capsActive);
         qDebug() << "emit pressedKey: m_capsActive = " << m_capsActive; // 
         

	}
    this->m_oldYKey = 0;

    if (tmpKeyBoard->isEmbeddedKeyboard() == true && NO_SPECIAL_KEY(text) && text.trimmed().length() != 0)
    {
        tmpKeyBoard->setCursor(Qt::BlankCursor);
        QCoreApplication::processEvents();
    }
}

// check if 
bool QKeyPushButton::isFunctionalKey(const QString& text)
{
    return IS_RETURN(text)
        || IS_BACK(text)
        || IS_BACK_EMB(text)
        || IS_SPACE(text);
}

void QKeyPushButton::mouseReleaseEvent(QMouseEvent * /* event */)
{
    widgetKeyBoard  *tmpKeyBoard = (widgetKeyBoard *) this->m_parent;
    bool            pressedEcho = IS_PASSWORD(this->text()) == true || IS_PASSWORD_EMB(this->text()) == true;

    if (IS_CAPS(this->text()) == false && pressedEcho == false)
    {

        if (tmpKeyBoard->isEmbeddedKeyboard() == true && NO_SPECIAL_KEY(this->text())  && this->text().trimmed().length() != 0)
        {
            tmpKeyBoard->setCursor(Qt::ArrowCursor);
            QCoreApplication::processEvents();
        }
                
        //if a functional key is pressed do not change the style of the button
        if (isFunctionalKey(this->text()))
        {
            this->setStyleSheet(
                QString(DEFAULT_STYLE_BUTTON)
              + QString(FUNCTIONAL_BUTTON_STYLE)
              + this->style_embedded
            );
        }
        else
        {
            this->setStyleSheet(
                QString(DEFAULT_STYLE_BUTTON)
              + QString(DEFAULT_BACKGROUND_BUTTON)
              + this->style_embedded
            );
        }
    }

    else if (pressedEcho == true && tmpKeyBoard->isEnabledSwitchingEcho() == false && tmpKeyBoard->currentTextBox()->echoMode() == QLineEdit::Normal)
        this->setStyleSheet(QString(DEFAULT_STYLE_BUTTON) + QString(DEFAULT_BACKGROUND_BUTTON) + this->style_embedded);
}


