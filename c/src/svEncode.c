/**
 * Rapid-prototyping protection schemes with IEC 61850
 *
 * Copyright (c) 2012 Steven Blair
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "svEncodeBasic.h"
#include "ied.h"
#include "svEncode.h"



int encode_myAnalogValue(unsigned char *buf, struct myAnalogValue *myAnalogValue) {
	int offset = 0;

	offset += ENCODE_CTYPE_FLOAT32(&buf[offset], &myAnalogValue->f);

	return offset;
}
int encode_ScaledValueConfig(unsigned char *buf, struct ScaledValueConfig *ScaledValueConfig) {
	int offset = 0;

	offset += ENCODE_CTYPE_FLOAT32(&buf[offset], &ScaledValueConfig->scaleFactor);
	offset += ENCODE_CTYPE_FLOAT32(&buf[offset], &ScaledValueConfig->offset);

	return offset;
}
int encode_myVector(unsigned char *buf, struct myVector *myVector) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &myVector->mag);
	offset += encode_myAnalogValue(&buf[offset], &myVector->ang);

	return offset;
}
int encode_simpleVector(unsigned char *buf, struct simpleVector *simpleVector) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &simpleVector->mag);
	offset += encode_myAnalogValue(&buf[offset], &simpleVector->ang);

	return offset;
}
int encode_myMod(unsigned char *buf, struct myMod *myMod) {
	int offset = 0;

	offset += ENCODE_CTYPE_ENUM(&buf[offset], &myMod->ctlVal);
	offset += ENCODE_CTYPE_ENUM(&buf[offset], &myMod->stVal);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &myMod->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &myMod->t);

	return offset;
}
int encode_myHealth(unsigned char *buf, struct myHealth *myHealth) {
	int offset = 0;

	offset += ENCODE_CTYPE_ENUM(&buf[offset], &myHealth->stVal);

	return offset;
}
int encode_myBeh(unsigned char *buf, struct myBeh *myBeh) {
	int offset = 0;

	offset += ENCODE_CTYPE_ENUM(&buf[offset], &myBeh->stVal);

	return offset;
}
int encode_myINS(unsigned char *buf, struct myINS *myINS) {
	int offset = 0;

	offset += ENCODE_CTYPE_INT32(&buf[offset], &myINS->stVal);

	return offset;
}
int encode_myLPL(unsigned char *buf, struct myLPL *myLPL) {
	int offset = 0;

	offset += ENCODE_CTYPE_VISSTRING255(&buf[offset], &myLPL->ldNs);
	offset += ENCODE_CTYPE_VISSTRING255(&buf[offset], &myLPL->configRev);

	return offset;
}
int encode_myDPL(unsigned char *buf, struct myDPL *myDPL) {
	int offset = 0;

	offset += ENCODE_CTYPE_VISSTRING255(&buf[offset], &myDPL->vendor);
	offset += ENCODE_CTYPE_VISSTRING255(&buf[offset], &myDPL->hwRev);

	return offset;
}
int encode_myPos(unsigned char *buf, struct myPos *myPos) {
	int offset = 0;

	offset += ENCODE_CTYPE_DBPOS(&buf[offset], &myPos->stVal);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &myPos->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &myPos->t);
	offset += ENCODE_CTYPE_BOOLEAN(&buf[offset], &myPos->ctlVal);

	return offset;
}
int encode_mySPS(unsigned char *buf, struct mySPS *mySPS) {
	int offset = 0;

	offset += ENCODE_CTYPE_INT32(&buf[offset], &mySPS->stVal);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &mySPS->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &mySPS->t);

	return offset;
}
int encode_myMV(unsigned char *buf, struct myMV *myMV) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &myMV->mag);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &myMV->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &myMV->t);
	offset += encode_ScaledValueConfig(&buf[offset], &myMV->sVC);

	return offset;
}
int encode_simpleMV(unsigned char *buf, struct simpleMV *simpleMV) {
	int offset = 0;

	offset += ENCODE_CTYPE_FLOAT32(&buf[offset], &simpleMV->mag);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &simpleMV->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &simpleMV->t);
	offset += encode_ScaledValueConfig(&buf[offset], &simpleMV->sVC);

	return offset;
}
int encode_simpleCMV(unsigned char *buf, struct simpleCMV *simpleCMV) {
	int offset = 0;

	offset += encode_simpleVector(&buf[offset], &simpleCMV->cVal);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &simpleCMV->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &simpleCMV->t);

	return offset;
}
int encode_simpleWYE(unsigned char *buf, struct simpleWYE *simpleWYE) {
	int offset = 0;

	offset += encode_simpleCMV(&buf[offset], &simpleWYE->phsA);
	offset += encode_simpleCMV(&buf[offset], &simpleWYE->phsB);
	offset += encode_simpleCMV(&buf[offset], &simpleWYE->phsC);

	return offset;
}
int encode_myCMV(unsigned char *buf, struct myCMV *myCMV) {
	int offset = 0;

	offset += encode_myVector(&buf[offset], &myCMV->cVal);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &myCMV->q);
	offset += ENCODE_CTYPE_TIMESTAMP(&buf[offset], &myCMV->t);

	return offset;
}
int encode_mySEQ(unsigned char *buf, struct mySEQ *mySEQ) {
	int offset = 0;

	offset += encode_myCMV(&buf[offset], &mySEQ->c1);
	offset += encode_myCMV(&buf[offset], &mySEQ->c2);
	offset += encode_myCMV(&buf[offset], &mySEQ->c3);
	offset += ENCODE_CTYPE_ENUM(&buf[offset], &mySEQ->seqT);

	return offset;
}
int encode_mySAV(unsigned char *buf, struct mySAV *mySAV) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &mySAV->instMag);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &mySAV->q);

	return offset;
}
int encode_simpleSAV(unsigned char *buf, struct simpleSAV *simpleSAV) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &simpleSAV->instMag);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &simpleSAV->q);

	return offset;
}
int encode_E1Q1SB1_C1_Positions(unsigned char *buf, int noASDU, CTYPE_INT16U smpCnt, struct E1Q1SB1_C1_Positions *E1Q1SB1_C1_Positions) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &E1Q1SB1_C1_Positions->C1__TVTR_1_Vol_instMag);
	offset += encode_myPos(&buf[offset], &E1Q1SB1_C1_Positions->C1__CSWI_1_Pos);
	offset += encode_myPos(&buf[offset], &E1Q1SB1_C1_Positions->C1__CSWI_2_Pos);
	offset += ENCODE_CTYPE_ENUM(&buf[offset], &E1Q1SB1_C1_Positions->C1__MMXU_1_Mod_stVal);
	offset += encode_myMV(&buf[offset], &E1Q1SB1_C1_Positions->C1__MMXU_1_Amps);
	offset += encode_myMV(&buf[offset], &E1Q1SB1_C1_Positions->C1__MMXU_1_Volts);

	return offset;
}
int encode_E1Q1SB1_C1_Measurands(unsigned char *buf, int noASDU, CTYPE_INT16U smpCnt, struct E1Q1SB1_C1_Measurands *E1Q1SB1_C1_Measurands) {
	int offset = 0;

	offset += encode_myMV(&buf[offset], &E1Q1SB1_C1_Measurands->C1__MMXU_1_Amps);
	offset += encode_myMV(&buf[offset], &E1Q1SB1_C1_Measurands->C1__MMXU_1_Volts);

	return offset;
}
int encode_E1Q1SB1_C1_smv(unsigned char *buf, int noASDU, CTYPE_INT16U smpCnt, struct E1Q1SB1_C1_smv *E1Q1SB1_C1_smv) {
	int offset = 0;

	offset += encode_myAnalogValue(&buf[offset], &E1Q1SB1_C1_smv->C1__TVTR_1_Vol_instMag);
	offset += encode_myMod(&buf[offset], &E1Q1SB1_C1_smv->C1__CSWI_1_Mod);
	offset += ENCODE_CTYPE_ENUM(&buf[offset], &E1Q1SB1_C1_smv->C1__MMXU_1_Mod_stVal);
	offset += ENCODE_CTYPE_QUALITY(&buf[offset], &E1Q1SB1_C1_smv->C1__MMXU_1_Volts_q);
	offset += encode_myMV(&buf[offset], &E1Q1SB1_C1_smv->C1__MMXU_1_Amps);
	offset += encode_myPos(&buf[offset], &E1Q1SB1_C1_smv->C1__CSWI_2_Pos);

	return offset;
}
int encode_E1Q1SB1_C1_rmxu(unsigned char *buf, int noASDU, CTYPE_INT16U smpCnt, struct E1Q1SB1_C1_rmxu *E1Q1SB1_C1_rmxu) {
	int offset = 0;

	offset += encode_simpleSAV(&buf[offset], &E1Q1SB1_C1_rmxu->C1__RMXU_1_AmpLocPhsA);
	offset += encode_simpleSAV(&buf[offset], &E1Q1SB1_C1_rmxu->C1__RMXU_1_AmpLocPhsB);
	offset += encode_simpleSAV(&buf[offset], &E1Q1SB1_C1_rmxu->C1__RMXU_1_AmpLocPhsC);

	return offset;
}
int encode_D1Q1SB4_C1_SyckResult(unsigned char *buf, int noASDU, CTYPE_INT16U smpCnt, struct D1Q1SB4_C1_SyckResult *D1Q1SB4_C1_SyckResult) {
	int offset = 0;

	offset += encode_mySPS(&buf[offset], &D1Q1SB4_C1_SyckResult->C1__RSYN_1_Rel);

	return offset;
}
int encode_D1Q1SB4_C1_MMXUResult(unsigned char *buf, int noASDU, CTYPE_INT16U smpCnt, struct D1Q1SB4_C1_MMXUResult *D1Q1SB4_C1_MMXUResult) {
	int offset = 0;

	offset += encode_simpleWYE(&buf[offset], &D1Q1SB4_C1_MMXUResult->C1__MMXU_1_A);

	return offset;
}


