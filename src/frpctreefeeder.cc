/*
 * FastRPC -- Fast RPC library compatible with XML-RPC
 * Copyright (C) 2005-7  Seznam.cz, a.s.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Seznam.cz, a.s.
 * Radlicka 2, Praha 5, 15000, Czech Republic
 * http://www.seznam.cz, mailto:fastrpc@firma.seznam.cz
 *
 * FILE          $Id: frpctreefeeder.cc,v 1.4 2008-04-01 13:19:07 burlog Exp $
 *
 * DESCRIPTION   
 *
 * AUTHOR        
 *              Miroslav Talasek <miroslav.talasek@firma.seznam.cz>
 *
 * HISTORY
 *       
 */

#include "frpctreefeeder.h"

namespace FRPC {

void TreeFeeder_t::feedValue(const Value_t &value){
    switch(value.getType()) {
    case Int_t::TYPE:
        {
            marshaller.packInt(Int(value).getValue());
        }
        break;

    case Bool_t::TYPE:
        {
            marshaller.packBool(Bool(value).getValue());
        }
        break;

    case Double_t::TYPE:
        {
            marshaller.packDouble(Double(value).getValue());
        }
        break;

    case String_t::TYPE:
        {
            const String_t &str = String(value);

            marshaller.packString(str.data(), str.size());
        }
        break;

    case Binary_t::TYPE:
        {
            const Binary_t &bin = Binary(value);

            marshaller.packBinary(bin.data(), bin.size());
        }
        break;

    case DateTime_t::TYPE:
        {
            const DateTime_t &dt = DateTime(value);

            marshaller.packDateTime(dt.getYear(), dt.getMonth(), dt.getDay(),
                                    dt.getHour(), dt.getMin(), dt.getSec(),
                                    dt.getDayOfWeek(), dt.getUnixTime(),
                                    dt.getTimeZone());

        }
        break;

    case Struct_t::TYPE:
        {
            const Struct_t &structVal = Struct(value);
            marshaller.packStruct(structVal.size());

            for (Struct_t::const_iterator
                     istructVal = structVal.begin(),
                     estructVal = structVal.end(); istructVal != estructVal;
                     ++istructVal)
            {
                marshaller.packStructMember(istructVal->first.data(),
                                            istructVal->first.size());

                feedValue(*(istructVal->second));
            }

        }
        break;

    case Array_t::TYPE:
        {
            const Array_t &array = Array(value);
            marshaller.packArray(array.size());
            for (Array_t::const_iterator
                     iarray = array.begin(),
                     earray = array.end(); iarray != earray; ++iarray)
            {
                feedValue(**iarray);
            }

        }
        break;


    }

}

TreeFeeder_t::~TreeFeeder_t()
{}

}
