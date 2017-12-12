#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <qrencode.h>

const QRecLevel REDUNDANCY_LEVEL = QR_ECLEVEL_L;

void qrprint(FILE *f, const char *s) {
	QRcode *qr = QRcode_encodeString(s, 0, REDUNDANCY_LEVEL, QR_MODE_8, 1);
	if (qr == NULL) {
		perror("test_encode_an aborted at QRcode_encodeString():");
		abort();
	}

	for (int i = 0; i < qr->width; i++) {
		for (int j = 0; j < qr->width; j++) {
			int black = qr->data[i*qr->width+j] & 1;
			if (black)
				fprintf(f, "██");
			else
				fprintf(f, "  ");
		}
		fprintf(f, "\n");
	}
}

int main() {
	char *address = strdup(getpass("Enter address: "));
	char *private_key = strdup(getpass("Enter private key: "));

	FILE *f = fopen(address, "w");

	fprintf(f, "Address: %s\n", address);
	qrprint(f, address);

	fprintf(f, "\n\n\n\n\n");

	fprintf(f, "Private key: %s\n", private_key);
	qrprint(f, private_key);

	fclose(f);

	return EXIT_SUCCESS;
}
