/*
 * Copyright (c) 2007 by Christian Dietrich <stettberger@dokucode.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <avr/io.h>

#include "core/bit-macros.h"
#include "protocols/uip/uip.h"
#include "config.h"
#include "snmp.h"
#include "snmp_net.h"

void
snmp_net_init(void)
{
  uip_udp_conn_t *conn;
  uip_ipaddr_t ip;
  uip_ipaddr_copy(&ip, all_ones_addr);

  if(! (conn = uip_udp_new(&ip, 0, snmp_net_main)))
    return; /* Couldn't bind socket */

  uip_udp_bind(conn, HTONS(SNMP_PORT));
}

void
snmp_net_main(void)
{
  if (uip_newdata())
    snmp_new_data();
}

/*
  -- Ethersex META --
  header(protocols/snmp/snmp_net.h)
  net_init(snmp_net_init)
*/