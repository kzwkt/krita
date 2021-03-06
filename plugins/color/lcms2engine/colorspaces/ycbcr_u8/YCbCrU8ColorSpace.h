/*
 *  Copyright (c) 2007 Cyrille Berger (cberger@cberger.net)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef KIS_YCBCR_U8_COLORSPACE_H_
#define KIS_YCBCR_U8_COLORSPACE_H_

#include <LcmsColorSpace.h>

#include <KoColorModelStandardIds.h>

#define TYPE_YCbCrA_8 (COLORSPACE_SH(PT_YCbCr)|CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1))

struct KoYCbCrU8Traits;

class YCbCrU8ColorSpace : public LcmsColorSpace<KoYCbCrU8Traits>
{
public:

    YCbCrU8ColorSpace(const QString &name, KoColorProfile *p);

    virtual bool willDegrade(ColorSpaceIndependence independence) const;

    static QString colorSpaceId()
    {
        return QString("YCBCRA8");
    }

    virtual KoID colorModelId() const
    {
        return YCbCrAColorModelID;
    }

    virtual KoID colorDepthId() const
    {
        return Integer8BitsColorDepthID;
    }

    virtual KoColorSpace *clone() const;

    virtual void colorToXML(const quint8 *pixel, QDomDocument &doc, QDomElement &colorElt) const;

    virtual void colorFromXML(quint8* pixel, const QDomElement& elt) const;
    virtual void toHSY(const QVector<double> &channelValues, qreal *hue, qreal *sat, qreal *luma) const;
    virtual QVector <double> fromHSY(qreal *hue, qreal *sat, qreal *luma) const;
    virtual void toYUV(const QVector<double> &channelValues, qreal *y, qreal *u, qreal *v) const;
    virtual QVector <double> fromYUV(qreal *y, qreal *u, qreal *v) const;

};

class YCbCrU8ColorSpaceFactory : public LcmsColorSpaceFactory
{
public:

    YCbCrU8ColorSpaceFactory() : LcmsColorSpaceFactory(TYPE_YCbCrA_8, cmsSigYCbCrData)
    {
    }

    virtual QString id() const
    {
        return YCbCrU8ColorSpace::colorSpaceId();
    }

    virtual QString name() const
    {
        return QString("%1 (%2)").arg(YCbCrAColorModelID.name()).arg(Integer8BitsColorDepthID.name());
    }

    virtual bool userVisible() const
    {
        return true;
    }

    virtual KoID colorModelId() const
    {
        return YCbCrAColorModelID;
    }

    virtual KoID colorDepthId() const
    {
        return Integer8BitsColorDepthID;
    }

    virtual int referenceDepth() const
    {
        return 8;
    }

    virtual KoColorSpace *createColorSpace(const KoColorProfile *p) const
    {
        return new YCbCrU8ColorSpace(name(), p->clone());
    }

    virtual QString defaultProfile() const
    {
        return QString();
    }
};

#endif
