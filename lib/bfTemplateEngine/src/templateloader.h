/**
  @file
  @author Stefan Frings
*/

#ifndef TEMPLATELOADER_H
#define TEMPLATELOADER_H

#include <QString>
#include <QSettings>
#include <QTextCodec>
#include <QMutex>

/**
  Loads localized versions of template files. If the caller requests a file with the
  name "index" and the suffix is ".tpl" and the requested locale is "de_DE, de, en-US",
  then files are searched in the following order:

  - index-de_DE.tpl
  - index-de.tpl
  - index-en_US.tpl  
  - index-en.tpl
  - index.tpl

  The following settings are required:
  <code><pre>
  path=.
  suffix=.tpl
  encoding=UTF-8
  </pre></code>
  The path is relative to the directory of the config file. In case of windows, if the
  settings are in the registry, the path is relative to the current working directory.
  @see TemplateCache
*/

class TemplateLoader : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(TemplateLoader);
public:

    /**
      Constructor.
      @param settings configurations settings
      @param parent parent object
    */
    TemplateLoader(QSettings* settings, QObject* parent=0);

    /** Destructor */
    virtual ~TemplateLoader();

protected:

    /**
      Try to get a file from cache or filesystem.
      @param localizedName Name of the template with locale to find
      @return The template document, or empty string if not found
    */
    virtual QString tryFile(QString localizedName);

    /** Directory where the templates are searched */
    QString templatePath;

    /** Suffix to the filenames */
    QString fileNameSuffix;

    /** Codec for decoding the files */
    QTextCodec* textCodec;

    /** Used to synchronize threads */
    QMutex mutex;
};

#endif // TEMPLATELOADER_H
