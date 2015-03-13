#include "parse.h"

Parser::Parser( std::string uifileuri )
{
  m_uifileuri = uifileuri ;
}

int Parser::parseXML( std::map< std::pair< QString , QString > , QString> & m )
    {
        /* We'll parse the example.xml */
        QFile* file = new QFile(m_uifileuri.data());

        /* If we can't open it, let's show an error message. */
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString errMsg = file->errorString();
            QFile::FileError err = QFile::NoError; //in Qt5, replace QFile by  QFileDevice
            err = file->error();
            qDebug() << err;
            return 1;
        }

        /* QXmlStreamReader takes any QIODevice. */
        QXmlStreamReader xml(file);

        /* We'll parse the XML until we reach end of it.*/
        while(!xml.atEnd() && !xml.hasError()) {

            QXmlStreamReader::TokenType token = xml.readNext();     // Read next element

            if(token == QXmlStreamReader::StartDocument) {      //If token is just StartDocument, we'll go to next
                continue;
            }

            else if (xml.qualifiedName() == "widget" && xml.isEndElement() != true)
            {
                if (xml.attributes().at(0).value().toString().compare("QTextEdit") == 0
                    || xml.attributes().at(0).value().toString().compare("QComboBox") == 0
                    || xml.attributes().at(0).value().toString().compare("QLineEdit") == 0)
                {
                    m[std::make_pair(xml.attributes().at(0).value().toString(), xml.attributes().at(1).value().toString())] = "QString";
//                    qDebug() << xml.attributes().at(0).value();     // Class type
//                    qDebug() << xml.attributes().at(1).value();     // Class name
                }

                else if (xml.attributes().at(0).value().toString().compare("QCheckBox") == 0
                         || xml.attributes().at(0).value().toString().compare("QRadioButton") == 0)
                {
                    m[std::make_pair(xml.attributes().at(0).value().toString(), xml.attributes().at(1).value().toString())] = "bool";
//                    qDebug() << xml.attributes().at(0).value();     // Class type
//                    qDebug() << xml.attributes().at(1).value();     // Class name
                }

                else if (xml.attributes().at(0).value().toString().compare("QDoubleSpinBox") == 0)
                {
                    m[std::make_pair(xml.attributes().at(0).value().toString(), xml.attributes().at(1).value().toString())] = "double";
//                    qDebug() << xml.attributes().at(0).value();     // Class type
//                    qDebug() << xml.attributes().at(1).value();     // Class name
                }

                else if (xml.attributes().at(0).value().toString().compare("QSpinBox") == 0
                         || xml.attributes().at(0).value().toString().compare("QScrollBar") == 0)
                {
                    m[std::make_pair(xml.attributes().at(0).value().toString(), xml.attributes().at(1).value().toString())] = "int";
//                    qDebug() << xml.attributes().at(0).value();     // Class type
//                    qDebug() << xml.attributes().at(1).value();     // Class name
                }

                else if (xml.attributes().at(0).value().toString().compare("QListWidget") == 0)
                {
                    qDebug() << xml.attributes().at(0).value();     // Class type
                    qDebug() << xml.attributes().at(1).value();     // Class name
                }
                // Store values into the dictionary
    //            m[std::make_pair(xml.attributes().at(0).value().toString(), xml.attributes().at(1).value().toString())] = "";

                // Print values to the console

            }

        }
        /* Error handling. */
        if(xml.hasError()) {

        }
        /* Removes any device() or data from the reader
         * and resets its internal state to the initial state. */
        xml.clear();

        file->close();
        delete file;

        return 0;
    }
