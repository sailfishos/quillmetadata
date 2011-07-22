/****************************************************************************
**
** Copyright (C) 2010-11 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Pekka Marjola <pekka.marjola@nokia.com>
**
** This file is part of the Quill Metadata package.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

extern "C" {
#include <setjmp.h>
#include <stdio.h>
#include <jpeglib.h>
}

#include <QTemporaryFile>

#include "exifwriteback.h"

struct my_error_mgr : public jpeg_error_mgr {
    jmp_buf setjmp_buffer;
};

static void my_error_exit (j_common_ptr cinfo)
{
    my_error_mgr* myerr = (my_error_mgr*) cinfo->err;
    longjmp(myerr->setjmp_buffer, 1);
}

bool ExifWriteback::writeback(const QString &fileName,
                              const QByteArray &exifSegment)
{
    struct jpeg_decompress_struct dinfo;
    struct jpeg_compress_struct cinfo;
    struct my_error_mgr derror, cerror;
    bool cinfo_inited = false;
    bool hasError = false;

    jpeg_create_decompress(&dinfo);

    FILE *fileIn = fopen(fileName.toAscii().constData(), "r");
    if (!fileIn)
        return false;

    jpeg_stdio_src(&dinfo, fileIn);

    dinfo.err = jpeg_std_error(&derror);
    derror.error_exit = my_error_exit;

    if (!setjmp(derror.setjmp_buffer)) {

        jpeg_save_markers(&dinfo, JPEG_COM, 0xFFFF);
        for (int i=0; i<16; i++)
            jpeg_save_markers(&dinfo, JPEG_APP0+i, 0xFFFF);

        jpeg_read_header(&dinfo, true);

        jvirt_barray_ptr *jpegData = jpeg_read_coefficients(&dinfo);

        FILE *fileOut = fopen(fileName.toAscii().constData(), "w");
        if (!fileOut)
            return false;

        cinfo_inited = true;
        jpeg_create_compress(&cinfo);
        cinfo.err = jpeg_std_error(&cerror);
        cerror.error_exit = my_error_exit;

        if (!setjmp(cerror.setjmp_buffer)) {

            jpeg_copy_critical_parameters(&dinfo, &cinfo);
            jpeg_stdio_dest(&cinfo, fileOut);

            jpeg_write_coefficients(&cinfo, jpegData);

            if (!exifSegment.isEmpty())
                jpeg_write_marker(&cinfo, JPEG_APP0+1,
                                  (const JOCTET*)exifSegment.constData(),
                                  exifSegment.size());

            jpeg_finish_compress(&cinfo);
        }
        else
            hasError = true;

        fclose(fileOut);
        jpeg_finish_decompress(&dinfo);
    }
    else
        hasError = true;

    fclose(fileIn);
    jpeg_destroy_decompress(&dinfo);
    if (cinfo_inited)
        jpeg_destroy_compress(&cinfo);

    return !hasError;
}
