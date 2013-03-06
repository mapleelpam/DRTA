
/*
 *  IHU -- I Hear U, easy VoIP application using Speex and Qt
 *
 *  Copyright (C) 2003-2005 M. Trotta - <mrotta@users.sourceforge.net>
 *
 *  http://ihu.sourceforge.net
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 */

/*
 *  MOD -- Messenger On-the-Drive
 *
 *  Copyright (C) 2006 Kai-Fong Chou - <mod.mapleelpam at gmail.com>
 *
 *  http://mod.0rz.net
 *  http://mod.sf.net
 *
 */

#include "Packet.h"
#include "Error.h"

Packet::Packet(int packetSize)
{
	size = packetSize;
	if ((packet = (char *)malloc(size))==NULL)
		throw Error(Error::DRTA_ERR_MEMORY);
	memset(packet, 0x0, size);
}

Packet::~Packet(void)
{
	free(packet);
}

void Packet::init(char *data, int len)
{
	strncpy(packet, HEADER_SYNC_STRING, HEADER_SYNC_LEN);
	packet[HEADER_SYNC_LEN] = (unsigned char) size;
	info = packet + HEADER_SYNC_LEN + 1; // Info
	dataLen = (unsigned char *) (packet + HEADER_SYNC_LEN + 2);
	*dataLen = (unsigned char) len;
	if (len > 0)
	{
		dataPtr = packet + HEADER_SIZE;
		memcpy(dataPtr, data, len);
	}
	resetInfo();
}

void Packet::resetInfo()
{
	*info = 0x0;
}

void Packet::setInfo(char param)
{
	*info |= param;
}

char Packet::getInfo()
{
	return (*info & 0x3f);
}

bool Packet::isInfo(char param)
{
	return (getInfo() & param);
}

char Packet::getMode()
{
	return (*info & 0xc0);
}

void Packet::fill(char *buffer, int len)
{
	memcpy(packet, buffer, len);
	dataPtr = packet + HEADER_SIZE;
	dataLen = (unsigned char *) dataPtr - 1;
	info = dataPtr - 2;
}

void Packet::crypt(Blowfish *blowfish)
{
	int len = *dataLen % DATA_BLOCK_SIZE;
	if (len)
		len = *dataLen + DATA_BLOCK_SIZE - len;
	else len = *dataLen;
	blowfish->encrypt(dataPtr, len);
}

void Packet::decrypt(Blowfish *blowfish)
{
	blowfish->decrypt(dataPtr, size - HEADER_SIZE);
}

int Packet::getSize()
{
	return size;
}

char * Packet::getPacket()
{
	return packet;
}

char * Packet::getData()
{
	return dataPtr;
}

int Packet::getDataLen()
{
	return (int) *dataLen;
}
