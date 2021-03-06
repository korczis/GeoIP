/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* test-geoip-org.c
 *
 * Copyright (C) 2006 MaxMind LLC
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "GeoIP.h"

int main (int argc, char* argv[]) {
	FILE *f;
	GeoIP * gi;
        char * org;
	int generate = 0;
	char host[50];

	if (argc == 2)
		if (!strcmp(argv[1],"gen"))
			generate = 1;

	gi = GeoIP_open("../data/GeoIPOrg.dat", GEOIP_INDEX_CACHE);

	if (gi == NULL) {
		fprintf(stderr, "Error opening database\n");
		exit(1);
	}

	f = fopen("org_test.txt","r");

	if (f == NULL) {
		fprintf(stderr, "Error opening org_test.txt\n");
		exit(1);
	}

	while (fscanf(f, "%s", host) != EOF) {
		org = GeoIP_name_by_name (gi, (const char *)host);

		if (org != NULL) {
			printf("%s\t%s\t%d\n", host, org, GeoIP_last_netmask(gi));
			free(org);
		}
	}

	fclose(f);
	GeoIP_delete(gi);
	return 0;
}
