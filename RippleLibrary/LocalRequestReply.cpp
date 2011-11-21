/*
* Copyright 2010-2011 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "Global.h"
#include "LocalRequestReply.h"
#include <QFileInfo>

LocalRequestReply::LocalRequestReply(const QUrl &url)
    : QNetworkReply()
{
    offset = 0;
    setUrl(url);
    QTimer::singleShot(0, this, SIGNAL(setContent()));

    types.insert("3gp", "video/3gpp");
    types.insert("a", "application/octet-stream");
    types.insert("ai", "application/postscript");
    types.insert("aif", "audio/x-aiff");
    types.insert("aiff", "audio/x-aiff");
    types.insert("asc", "application/pgp-signature");
    types.insert("asf", "video/x-ms-asf");
    types.insert("asm", "text/x-asm");
    types.insert("asx", "video/x-ms-asf");
    types.insert("atom", "application/atom+xml");
    types.insert("au", "audio/basic");
    types.insert("avi", "video/x-msvideo");
    types.insert("bat", "application/x-msdownload");
    types.insert("bin", "application/octet-stream");
    types.insert("bmp", "image/bmp");
    types.insert("bz2", "application/x-bzip2");
    types.insert("c", "text/x-c");
    types.insert("cab", "application/vnd.ms-cab-compressed");
    types.insert("cc", "text/x-c");
    types.insert("chm", "application/vnd.ms-htmlhelp");
    types.insert("class", "application/octet-stream");
    types.insert("com", "application/x-msdownload");
    types.insert("conf", "text/plain");
    types.insert("cpp", "text/x-c");
    types.insert("crt", "application/x-x509-ca-cert");
    types.insert("css", "text/css");
    types.insert("csv", "text/csv");
    types.insert("cxx", "text/x-c");
    types.insert("deb", "application/x-debian-package");
    types.insert("der", "application/x-x509-ca-cert");
    types.insert("diff", "text/x-diff");
    types.insert("djv", "image/vnd.djvu");
    types.insert("djvu", "image/vnd.djvu");
    types.insert("dll", "application/x-msdownload");
    types.insert("dmg", "application/octet-stream");
    types.insert("doc", "application/msword");
    types.insert("dot", "application/msword");
    types.insert("dtd", "application/xml-dtd");
    types.insert("dvi", "application/x-dvi");
    types.insert("ear", "application/java-archive");
    types.insert("eml", "message/rfc822");
    types.insert("eps", "application/postscript");
    types.insert("exe", "application/x-msdownload");
    types.insert("f", "text/x-fortran");
    types.insert("f77", "text/x-fortran");
    types.insert("f90", "text/x-fortran");
    types.insert("flv", "video/x-flv");
    types.insert("for", "text/x-fortran");
    types.insert("gem", "application/octet-stream");
    types.insert("gemspec", "text/x-script.ruby");
    types.insert("gif", "image/gif");
    types.insert("gz", "application/x-gzip");
    types.insert("h", "text/x-c");
    types.insert("hh", "text/x-c");
    types.insert("htm", "text/html");
    types.insert("html", "text/html");
    types.insert("insert(co", "image/vnd.microsoft.insert(con");
    types.insert("insert(cs", "text/calendar");
    types.insert("insert(fb", "text/calendar");
    types.insert("insert(so", "application/octet-stream");
    types.insert("jar", "application/java-archive");
    types.insert("java", "text/x-java-source");
    types.insert("jnlp", "application/x-java-jnlp-file");
    types.insert("jpeg", "image/jpeg");
    types.insert("jpg", "image/jpeg");
    types.insert("js", "application/javascript");
    types.insert("json", "application/json");
    types.insert("log", "text/plain");
    types.insert("m3u", "audio/x-mpegurl");
    types.insert("m4v", "video/mp4");
    types.insert("man", "text/troff");
    types.insert("mathml", "application/mathml+xml");
    types.insert("mbox", "application/mbox");
    types.insert("mdoc", "text/troff");
    types.insert("me", "text/troff");
    types.insert("mid", "audio/midi");
    types.insert("midi", "audio/midi");
    types.insert("mime", "message/rfc822");
    types.insert("mml", "application/mathml+xml");
    types.insert("mng", "video/x-mng");
    types.insert("mov", "video/quicktime");
    types.insert("mp3", "audio/mpeg");
    types.insert("mp4", "video/mp4");
    types.insert("mp4v", "video/mp4");
    types.insert("mpeg", "video/mpeg");
    types.insert("mpg", "video/mpeg");
    types.insert("ms", "text/troff");
    types.insert("msi", "application/x-msdownload");
    types.insert("odp", "application/vnd.oasis.opendocument.presentation");
    types.insert("ods", "application/vnd.oasis.opendocument.spreadsheet");
    types.insert("odt", "application/vnd.oasis.opendocument.text");
    types.insert("ogg", "application/ogg");
    types.insert("p", "text/x-pascal");
    types.insert("pas", "text/x-pascal");
    types.insert("pbm", "image/x-portable-bitmap");
    types.insert("pdf", "application/pdf");
    types.insert("pem", "application/x-x509-ca-cert");
    types.insert("pgm", "image/x-portable-graymap");
    types.insert("pgp", "application/pgp-encrypted");
    types.insert("pkg", "application/octet-stream");
    types.insert("pl", "text/x-script.perl");
    types.insert("pm", "text/x-script.perl-module");
    types.insert("png", "image/png");
    types.insert("pnm", "image/x-portable-anymap");
    types.insert("ppm", "image/x-portable-pixmap");
    types.insert("pps", "application/vnd.ms-powerpoint");
    types.insert("ppt", "application/vnd.ms-powerpoint");
    types.insert("ps", "application/postscript");
    types.insert("psd", "image/vnd.adobe.photoshop");
    types.insert("py", "text/x-script.python");
    types.insert("qt", "video/quicktime");
    types.insert("ra", "audio/x-pn-realaudio");
    types.insert("rake", "text/x-script.ruby");
    types.insert("ram", "audio/x-pn-realaudio");
    types.insert("rar", "application/x-rar-compressed");
    types.insert("rb", "text/x-script.ruby");
    types.insert("rdf", "application/rdf+xml");
    types.insert("roff", "text/troff");
    types.insert("rpm", "application/x-redhat-package-manager");
    types.insert("rss", "application/rss+xml");
    types.insert("rtf", "application/rtf");
    types.insert("ru", "text/x-script.ruby");
    types.insert("s", "text/x-asm");
    types.insert("sgm", "text/sgml");
    types.insert("sgml", "text/sgml");
    types.insert("sh", "application/x-sh");
    types.insert("sig", "application/pgp-signature");
    types.insert("snd", "audio/basic");
    types.insert("so", "application/octet-stream");
    types.insert("svg", "image/svg+xml");
    types.insert("svgz", "image/svg+xml");
    types.insert("swf", "application/x-shockwave-flash");
    types.insert("t", "text/troff");
    types.insert("tar", "application/x-tar");
    types.insert("tbz", "application/x-bzip-compressed-tar");
    types.insert("tcl", "application/x-tcl");
    types.insert("tex", "application/x-tex");
    types.insert("texi", "application/x-texinfo");
    types.insert("texinfo", "application/x-texinfo");
    types.insert("text", "text/plain");
    types.insert("tif", "image/tiff");
    types.insert("tiff", "image/tiff");
    types.insert("torrent", "application/x-bittorrent");
    types.insert("tr", "text/troff");
    types.insert("txt", "text/plain");
    types.insert("vcf", "text/x-vcard");
    types.insert("vcs", "text/x-vcalendar");
    types.insert("vrml", "model/vrml");
    types.insert("war", "application/java-archive");
    types.insert("wav", "audio/x-wav");
    types.insert("wma", "audio/x-ms-wma");
    types.insert("wmv", "video/x-ms-wmv");
    types.insert("wmx", "video/x-ms-wmx");
    types.insert("wrl", "model/vrml");
    types.insert("wsdl", "application/wsdl+xml");
    types.insert("xbm", "image/x-xbitmap");
    types.insert("xhtml", "application/xhtml+xml");
    types.insert("xls", "application/vnd.ms-excel");
    types.insert("xml", "application/xml");
    types.insert("xpm", "image/x-xpixmap");
    types.insert("xsl", "application/xml");
    types.insert("xslt", "application/xslt+xml");
    types.insert("yaml", "text/yaml");
    types.insert("yml", "text/yaml");
    types.insert("zip", "application/zip");
}


qint64 LocalRequestReply::readData(char *data, qint64 maxSize)
{
    if (offset < content.size()) {
        qint64 number = qMin(maxSize, content.size() - offset);
        memcpy(data, content.constData() + offset, number);
        offset += number;
        return number;
    } else {
        return -1;
    }
}

bool LocalRequestReply::isSequential() const
{
    return true;
}

qint64 LocalRequestReply::bytesAvailable() const
{
    //Calling QNetworkReply::bytesAvailable() is required by all QNetworkReply
    //sub classes that return isSequential = true.
    //See QIODevice.cpp - bytesAvailable for documentation
    return content.size() + QNetworkReply::bytesAvailable() - offset;
}

void LocalRequestReply::setContent()
{
    QString path = this->url().toString();
    QStringList split = path.split(LOCAL_PROTOCOL);

    if (split.length() == 2) {
        path = LOCAL_BASE_PATH + split.at(1);
        QFile file(path);
        QFileInfo fileInfo(path);

        if (fileInfo.exists() && file.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
            content = file.readAll();
            file.close();
            open(ReadOnly | Unbuffered);
            setAttribute(QNetworkRequest::HttpStatusCodeAttribute, QVariant(200));
            setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.size()));
            setHeader(QNetworkRequest::ContentTypeHeader, QVariant(types[fileInfo.completeSuffix()]));

            emit readyRead();
            emit finished();
            return;
        }
    }

    open(ReadOnly | Unbuffered);
    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, QVariant(404));
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(0));

    emit readyRead();
    emit finished();
}
