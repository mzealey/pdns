/*
    PowerDNS Versatile Database Driven Nameserver
    Copyright (C) 2002 - 2007 PowerDNS.COM BV

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation
    

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "utility.hh"
#include "dns.hh"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include "qtype.hh"
#include "misc.hh"
#include "lock.hh"

map<string,uint16_t> QType::names_map;
map<uint16_t,string> QType::numbers_map;

// XXX FIXME we need to do something with initializer order here!
QType::init QType::initializer; 

QType::QType()
{
}

uint16_t QType::getCode() const
{
  return code;
}

const string QType::getName() const
{
  if( numbers_map.count(code) )
      return numbers_map[code];

  return "TYPE"+itoa(code);
}

QType &QType::operator=(uint16_t n)
{
  code=n;
  return *this;
}

int QType::chartocode(const char *p)
{
  string search = p;
  if( names_map.count(search) )
    return names_map[search];
  
  if(*p=='#') {
    return atoi(p+1);
  }

  if(boost::starts_with(p, "TYPE"))
    return atoi(p+4);
    
  return 0;
}

QType &QType::operator=(const char *p)
{
  code=chartocode(p);
  return *this;
}

QType &QType::operator=(const string &s)
{
  code=chartocode(s.c_str());
  return *this;
}


QType::QType(uint16_t n)
{
  QType();
  code=n;
}
