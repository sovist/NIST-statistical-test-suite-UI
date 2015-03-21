/* --------------------------------------------------------------------------
   Title       :  The NIST Statistical Test Suite

   Date        :  December 1999

   Programmer  :  Juan Soto

   Summary     :  For use in the evaluation of the randomness of bitstreams
                  produced by cryptographic random number generators.

   Package     :  Version 1.0

   Copyright   :  (c) 1999 by the National Institute Of Standards & Technology

   History     :  Version 1.0 by J. Soto, October 1999
                  Revised by J. Soto, November 1999
                  Revised by Larry Bassham, March 2008

   Keywords    :  Pseudorandom Number Generator (PRNG), Randomness, Statistical 
                  Tests, Complementary Error functions, Incomplete Gamma 
                  Function, Random Walks, Rank, Fast Fourier Transform, 
                  Template, Cryptographically Secure PRNG (CSPRNG),
                  Approximate Entropy (ApEn), Secure Hash Algorithm (SHA-1), 
                  Blum-Blum-Shub (BBS) CSPRNG, Micali-Schnorr (MS) CSPRNG, 

   Source      :  David Banks, Elaine Barker, James Dray, Allen Heckert, 
                  Stefan Leigh, Mark Levenson, James Nechvatal, Andrew Rukhin, 
                  Miles Smid, Juan Soto, Mark Vangel, and San Vo.

   Technical
   Assistance  :  Larry Bassham, Ron Boisvert, James Filliben, Daniel Lozier,
                  and Bert Rust.

   Warning     :  Portability Issues.

   Limitation  :  Amount of memory allocated for workspace.

   Restrictions:  Permission to use, copy, and modify this software without 
                  fee is hereby granted, provided that this entire notice is 
                  included in all copies of any software which is or includes
                  a copy or modification of this software and in all copies 
                  of the supporting documentation for such software.
   -------------------------------------------------------------------------- */

#include <stdio.h>   /* defines FILENAME_MAX */
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "include/decls.h"
#include "include/cephes.h"  
#include "include/utilities.h"
//#include "../NIST_UI/assess.h"
 
#include <direct.h>
#define GetCurrentDir _getcwd

using namespace System;

char* NIST_Main(/*int argc, char *argv[],*/ InitNISTParam *initParam)
{
	int		i;
	int		option;			/* TEMPLATE LENGTH/STREAM LENGTH/GENERATOR*/
	char	*streamFile;	/* STREAM FILENAME     */

//    _initParam = initParam;
	/*if ( argc != 2 ) {
		printf("Usage: %s <stream length>\n", argv[0]);
		printf("   <stream length> is the length of the individual bit stream(s) to be processed\n");
		getchar();
		return 0;
	}*/
    SetInitNISTParam(initParam);
    initParam->CopyParam(tp);

	/*tp.n = atoi(argv[1]);
	tp.blockFrequencyBlockLength = 128;
	tp.nonOverlappingTemplateBlockLength = 9;
	tp.overlappingTemplateBlockLength = 9;
	tp.approximateEntropyBlockLength = 10;
	tp.serialBlockLength = 16;
	tp.linearComplexitySequenceLength = 500;
	tp.numOfBitStreams = 1;*/

     option = generatorOptions(&streamFile, initParam->GetGenertorSelectionIndex(), initParam->GetInputFileName());
	//chooseTests();

    for( i = 0; i <= NUMOFTESTS; i++ )
        testVector[i] = initParam->GetStatisticalTestVector()[i];

	//fixParameters();
	openOutputStreams(option);
    invokeTestSuite(option, streamFile, initParam->GetReadFileMode());
	fclose(freqfp);

	for( i=1; i<=NUMOFTESTS; i++ ) 
	{
		if ( stats[i] != NULL )
			fclose(stats[i]);
		if ( results[i] != NULL )
			fclose(results[i]);
	}

	if ( (testVector[0] == 1) || (testVector[TEST_CUSUM] == 1) ) 
		partitionResultFile(2, tp.numOfBitStreams, option, TEST_CUSUM);
	initParam->incProgress();

	if ( (testVector[0] == 1) || (testVector[TEST_NONPERIODIC] == 1) ) 
		partitionResultFile(MAXNUMOFTEMPLATES, tp.numOfBitStreams, option, TEST_NONPERIODIC);
	initParam->incProgress();

	if ( (testVector[0] == 1) || (testVector[TEST_RND_EXCURSION] == 1) )
		partitionResultFile(8, tp.numOfBitStreams, option, TEST_RND_EXCURSION);
	initParam->incProgress();

	if ( (testVector[0] == 1) || (testVector[TEST_RND_EXCURSION_VAR] == 1) )
		partitionResultFile(18, tp.numOfBitStreams, option, TEST_RND_EXCURSION_VAR);
	initParam->incProgress();

	if ( (testVector[0] == 1) || (testVector[TEST_SERIAL] == 1) )
		partitionResultFile(2, tp.numOfBitStreams, option, TEST_SERIAL);
	initParam->incProgress();

	fprintf(summary, "------------------------------------------------------------------------------\n");
	fprintf(summary, "RESULTS FOR THE UNIFORMITY OF P-VALUES AND THE PROPORTION OF PASSING SEQUENCES\n");
	fprintf(summary, "------------------------------------------------------------------------------\n");
	fprintf(summary, "   generator is <%s>\n", streamFile);
	fprintf(summary, "------------------------------------------------------------------------------\n");
	fprintf(summary, " C1  C2  C3  C4  C5  C6  C7  C8  C9 C10  P-VALUE  PROPORTION  STATISTICAL TEST\n");
	fprintf(summary, "------------------------------------------------------------------------------\n");
	postProcessResults(option, initParam);
	fclose(summary);

    char cCurrentPath[FILENAME_MAX];
    GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));

    char* fileName = new char[1024];   
    sprintf(fileName, "%s\\experiments\\%s\\"/*finalAnalysisReport.txt"*/, cCurrentPath, generatorDir[option]);

	return fileName;
}

void
partitionResultFile(int numOfFiles, int numOfSequences, int option, int testNameID)
{ 
	int		i, k, m, j, start, end, num, numread;
	float	c;
	FILE	**fp = (FILE **)calloc(numOfFiles+1, sizeof(FILE *));
	int		*results = (int *)calloc(numOfFiles, sizeof(int *));
	char	*s[MAXFILESPERMITTEDFORPARTITION];
	char	resultsDir[200];
	
	for ( i=0; i<MAXFILESPERMITTEDFORPARTITION; i++ )
		s[i] = (char*)calloc(200, sizeof(char));
	
	sprintf(resultsDir, "experiments/%s/%s/results.txt", generatorDir[option], testNames[testNameID]);
	
	if ( (fp[numOfFiles] = fopen(resultsDir, "r")) == NULL ) 
    {
		//printf("%s", resultsDir);
		//printf(" -- file not found. Exiting program.\n");
		//exit(-1);
        throw gcnew Exception("file not found: " + (const char)resultsDir);
	}
	
	for ( i=0; i<numOfFiles; i++ ) 
	{
		if ( i < 10 )
			sprintf(s[i], "experiments/%s/%s/data%1d.txt", generatorDir[option], testNames[testNameID], i+1);
		else if (i < 100)
			sprintf(s[i], "experiments/%s/%s/data%2d.txt", generatorDir[option], testNames[testNameID], i+1);
		else
			sprintf(s[i], "experiments/%s/%s/data%3d.txt", generatorDir[option], testNames[testNameID], i+1);
	}
	numread = 0;
	m = numOfFiles/20;
	if ( (numOfFiles%20) != 0 )
		m++;
	for ( i=0; i<numOfFiles; i++ ) 
	{
		if ( (fp[i] = fopen(s[i], "w")) == NULL ) 
        {
			//printf("%s", s[i]);
			//printf(" -- file not found. Exiting program.\n");
			//exit(-1);
            throw gcnew Exception("file not found: " + (const char)s[i]);
		}
		fclose(fp[i]);
	}
	for ( num=0; num<numOfSequences; num++ ) 
	{
		for ( k=0; k<m; k++ ) 
		{ 			/* FOR EACH BATCH */
			
			start = k*20;		/* BOUNDARY SEGMENTS */
			end   = k*20+19;
			if ( k == (m-1) )
				end = numOfFiles-1;
			
			for ( i=start; i<=end; i++ ) 
            {		/* OPEN FILE */
				if ( (fp[i] = fopen(s[i], "a")) == NULL ) 
                {
					/*printf("%s", s[i]);
					printf(" -- file not found. Exiting program.\n");
					exit(-1);*/
                    throw gcnew Exception("file not found: " + (const char)s[i]);
				}
			}
			
			for ( j=start; j<=end; j++ ) 
            {		/* POPULATE FILE */
				fscanf_s(fp[numOfFiles], "%f", &c);
				fprintf(fp[j], "%f\n", c);
				numread++;
			}

			for ( i=start; i<=end; i++ )		/* CLOSE FILE */
				fclose(fp[i]);
		}
	}
	fclose(fp[numOfFiles]);
	for ( i=0; i<MAXFILESPERMITTEDFORPARTITION; i++ )
		free(s[i]);

	return;
}

/*int
cmp(const double *a, const double *b)
{
	if ( *a < *b )
		return -1;
	if ( *a == *b )
		return 0;
	return 1;
}*/

int __cdecl cmp(const void *a, const void *b)
{
	if ( *((double*)a) < *((double*)b) )
		return -1;

	if ( *((double*)a) == *((double*)b) )
		return 0;

	return 1;
}

void
postProcessResults(int option, InitNISTParam* initNISTParam)
{
	int		i, k, randomExcursionSampleSize, generalSampleSize;
	int		passRate, case1, case2, numOfFiles = 2;
	double	p_hat;
	char	s[200];
	
	for ( i=1; i<=NUMOFTESTS; i++ ) 
	{		// FOR EACH TEST
		if ( testVector[i] ) 
		{
			// SPECIAL CASES -- HANDLING MULTIPLE FILES FOR A SINGLE TEST
			if ( ((i == TEST_CUSUM) && testVector[TEST_CUSUM] ) ||
				 ((i == TEST_NONPERIODIC) && testVector[TEST_NONPERIODIC] ) ||
				 ((i == TEST_RND_EXCURSION) && testVector[TEST_RND_EXCURSION]) ||
				 ((i == TEST_RND_EXCURSION_VAR) && testVector[TEST_RND_EXCURSION_VAR]) || 
				 ((i == TEST_SERIAL) && testVector[TEST_SERIAL]) ) 
			{
				
				if ( (i == TEST_NONPERIODIC) && testVector[TEST_NONPERIODIC] )  
					numOfFiles = MAXNUMOFTEMPLATES;
				else if ( (i == TEST_RND_EXCURSION) && testVector[TEST_RND_EXCURSION] ) 
					numOfFiles = 8;
				else if ( (i == TEST_RND_EXCURSION_VAR) && testVector[TEST_RND_EXCURSION_VAR] ) 
					numOfFiles = 18;
				else
					numOfFiles = 2;
				for ( k=0; k<numOfFiles; k++ ) 
				{
					if ( k < 10 )
						sprintf(s, "experiments/%s/%s/data%1d.txt", generatorDir[option], testNames[i], k+1);
					else if ( k < 100 )
						sprintf(s, "experiments/%s/%s/data%2d.txt", generatorDir[option], testNames[i], k+1);
					else
						sprintf(s, "experiments/%s/%s/data%3d.txt", generatorDir[option], testNames[i], k+1);
					if ( (i == TEST_RND_EXCURSION) || (i == TEST_RND_EXCURSION_VAR) ) 
						randomExcursionSampleSize = computeMetrics(s,i);
					else
						generalSampleSize = computeMetrics(s,i);
				}
			}
			else 
			{
				sprintf(s, "experiments/%s/%s/results.txt", generatorDir[option], testNames[i]);
				generalSampleSize = computeMetrics(s,i);
			}
		}
	 initNISTParam->incProgress();
	}

	fprintf(summary, "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	case1 = 0;
	case2 = 0;
	if ( testVector[TEST_RND_EXCURSION] || testVector[TEST_RND_EXCURSION_VAR] ) 
		case2 = 1;
	for ( i=1; i<=NUMOFTESTS; i++ ) 
	{
		if ( testVector[i] && (i != TEST_RND_EXCURSION) && (i != TEST_RND_EXCURSION_VAR) ) 
		{
			case1 = 1;
			break;
		}
	}
	p_hat = 1.0 - ALPHA;
	if ( case1 ) 
    {
		if ( generalSampleSize == 0 ) 
		{		
			if (initNISTParam->GetCulture() == "en-US")
			{
				fprintf(summary, "The minimum pass rate for each statistical test with the exception of the\n");
				fprintf(summary, "random excursion (variant) test is undefined.\n\n");
			}
			if (initNISTParam->GetCulture() == "ru-RU")
			{
				fprintf(summary, "Минимальное проходное значение для каждого статистического теста, за исключением\n");
				fprintf(summary, "тестов random excursion (variant) не определено.\n\n");			
			}
			if (initNISTParam->GetCulture() == "uk-UA")
			{
				fprintf(summary, "Мінімальне прохідне значення для кожного статистичного тесту, за винятком\n");
				fprintf(summary, "тестів random excursion (variant) є не визнеченою.\n\n");
			}
		}
		else 
        {
			passRate = (int)((p_hat - 3.0 * sqrt((p_hat*ALPHA)/generalSampleSize)) * generalSampleSize);

			if (initNISTParam->GetCulture() == "en-US")
			{
				fprintf(summary, "The minimum pass rate for each statistical test with the exception of the\n");
				//fprintf(summary, "random excursion (variant) test is approximately = %d for a\n", generalSampleSize ? passRate : 0);
				fprintf(summary, "random excursion (variant) test is approximately = %1.3f for a\n", (double)passRate/generalSampleSize);
				fprintf(summary, "sample size = %d binary sequences.\n\n", generalSampleSize);
			}
			if (initNISTParam->GetCulture() == "ru-RU")
			{
				fprintf(summary, "Минимальное проходное значение для каждого статистического теста, за исключением\n");
				fprintf(summary, "тестов random excursion (variant) примерно = %1.3f\n\n", (double)passRate/generalSampleSize);
				//fprintf(summary, "%d двоичных последовательностей.\n\n", generalSampleSize);			
			}
			if (initNISTParam->GetCulture() == "uk-UA")
			{
				fprintf(summary, "Мінімальне прохідне значення для кожного статистичного тесту, за винятком\n");
				fprintf(summary, "тестів random excursion (variant) приблизно = %1.3f\n\n", (double)passRate/generalSampleSize);
				//fprintf(summary, "%d двійкових послідовновностей.\n\n", generalSampleSize);
			}
		}
	}
	if ( case2 ) 
    {
		if ( randomExcursionSampleSize == 0 )
		{		
			if (initNISTParam->GetCulture() == "en-US")
			    fprintf(summary, "The minimum pass rate for the random excursion (variant) test is undefined.\n\n");

			if (initNISTParam->GetCulture() == "ru-RU")
			    fprintf(summary, "Минимальное проходное значение для тестов random excursion (variant) не определено.\n");

			if (initNISTParam->GetCulture() == "uk-UA")
			    fprintf(summary, "Мінімальне прохідне значення для тестів random excursion (variant) не визначено.\n");
		}
		else 
        {
			passRate = (int)((p_hat - 3.0 * sqrt((p_hat*ALPHA)/randomExcursionSampleSize)) * randomExcursionSampleSize);

			if (initNISTParam->GetCulture() == "en-US")
			{
				fprintf(summary, "The minimum pass rate for the random excursion (variant) test\n");
				//fprintf(summary, "is approximately = %d for a sample size = %d binary sequences.\n\n", passRate, randomExcursionSampleSize);
				fprintf(summary, "is approximately = %1.3f for a sample size = %d binary sequences.\n\n", (double)passRate/randomExcursionSampleSize, randomExcursionSampleSize);
			}
			if (initNISTParam->GetCulture() == "ru-RU")
			{	
				fprintf(summary, "Минимальное проходное значение для тестов random excursion (variant)\n");
				fprintf(summary, "примерно = %1.3f\n", (double)passRate/randomExcursionSampleSize);
			}
			if (initNISTParam->GetCulture() == "uk-UA")
			{
				fprintf(summary, "Мінімальне прохідне значення для тестів random excursion (variant)\n");
				fprintf(summary, "приблизно = %1.3f\n", (double)passRate/randomExcursionSampleSize);
			}
		}
	}
	//fprintf(summary, "For further guidelines construct a probability table using the MAPLE program\n");
	//fprintf(summary, "provided in the addendum section of the documentation.\n");
	fprintf(summary, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

int
computeMetrics(char *s, int test)
{
	int		j, pos, count, passCount, sampleSize, expCount, proportion_threshold_min, proportion_threshold_max;
	int		freqPerBin[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double	*A, *T, chi2, uniformity, p_hat/*,  proportion, tmp*/;
	float	c;
	FILE	*fp;
	
	if ( (fp = fopen(s, "r")) == NULL ) 
    {
		//printf("%s",s);
		//printf(" -- file not found. Exiting program.\n");
		//exit(-1);
        throw gcnew Exception("file not found: " + (const char)s);
	}
	
	if ( (A = (double *)calloc(tp.numOfBitStreams, sizeof(double))) == NULL ) 
    {
		//printf("Final Analysis Report aborted due to insufficient workspace\n");
		//return 0;
        throw gcnew Exception("Final Analysis Report aborted due to insufficient workspace");
	}
	
	/* Compute Metric 1: Proportion of Passing Sequences */
	
	count = 0; 		
	sampleSize = tp.numOfBitStreams;
	
	if ( (test == TEST_RND_EXCURSION) || (test == TEST_RND_EXCURSION_VAR) ) 
    { /* Special Case: Random Excursion Tests */
		if ( (T = (double *)calloc(tp.numOfBitStreams, sizeof(double))) == NULL ) 
        {
			//printf("Final Analysis Report aborted due to insufficient workspace\n");
			//return 0;
            throw gcnew Exception("Final Analysis Report aborted due to insufficient workspace");
		}
		for ( j=0; j<sampleSize; j++ ) {
			fscanf_s(fp, "%f", &c);
			if ( c > 0.000000 )
				T[count++] = c;
		}
		
		if ( (A = (double *)calloc(count, sizeof(double))) == NULL ) 
        {
			//printf("Final Analysis Report aborted due to insufficient workspace\n");
			//return 0;
            throw gcnew Exception("Final Analysis Report aborted due to insufficient workspace");
		}
		
		for ( j=0; j<count; j++ )
			A[j] = T[j];
		
		sampleSize = count;
		count = 0;
		for ( j=0; j<sampleSize; j++ )
			if ( A[j] < ALPHA )
				count++;
		free(T);
	}
	else {
		if ( (A = (double *)calloc(sampleSize, sizeof(double))) == NULL ) 
        {
			//printf("Final Analysis Report aborted due to insufficient workspace\n");
			//return 0;
            throw gcnew Exception("Final Analysis Report aborted due to insufficient workspace");
		}
		for ( j=0; j<sampleSize; j++ ) {
			fscanf_s(fp, "%f", &c);
			if ( c < ALPHA )
				count++;
			A[j] = c;
		}
	}
	if ( sampleSize == 0 )
		passCount = 0;
	else
		passCount = sampleSize - count;
	
	p_hat = 1.0 - ALPHA;
	proportion_threshold_max = (int)((p_hat + 3.0 * sqrt((p_hat*ALPHA)/sampleSize)) * sampleSize);
	proportion_threshold_min = (int)((p_hat - 3.0 * sqrt((p_hat*ALPHA)/sampleSize)) * sampleSize);
	
	/* Compute Metric 2: Histogram */
	/*_*/

	qsort((void *)A, sampleSize, sizeof(double), cmp);
	for ( j=0; j<sampleSize; j++ ) {
		pos = (int)floor(A[j]*10);
		if ( pos == 10 )
			pos--;
		freqPerBin[pos]++;
	}
	chi2 = 0.0;
	expCount = sampleSize/10;
	if ( expCount == 0 )
		uniformity = 0.0;
	else {
		for ( j=0; j<10; j++ )
			chi2 += pow((double)freqPerBin[j]-expCount, 2)/expCount;
		uniformity = cephes_igamc(9.0/2.0, chi2/2.0);
	}
	
	for ( j=0; j<10; j++ )			/* DISPLAY RESULTS */
		fprintf(summary, "%3d ", freqPerBin[j]);
	
	if ( expCount == 0 )
		fprintf(summary, "   ----     ");
	else 
       // if ( uniformity < 0.0001 )
		//   fprintf(summary, " %8.6f * ", uniformity);
	   //else
		   fprintf(summary, " %8.6f   ", uniformity);
	
	if ( sampleSize == 0 )
		fprintf(summary, "-----    %s\n", testNames[test]);
	//	else if ( proportion < 0.96 )
	else if ( (passCount < proportion_threshold_min) || (passCount > proportion_threshold_max))
		//fprintf(summary, "%4d/%-4d *  %s\n", passCount, sampleSize, testNames[test]);
        if ( uniformity < 0.0001 )
           fprintf(summary,    "%1.3f ** %s\n", ((double)passCount/sampleSize), testNames[test]);
        else
           fprintf(summary,    "%1.3f *  %s\n", ((double)passCount/sampleSize), testNames[test]);
	else
		//fprintf(summary, "%4d/%-4d    %s\n", passCount, sampleSize, testNames[test]);
        //fprintf(summary,    "%1.3f    %s\n", ((double)passCount/sampleSize), testNames[test]);
        if ( uniformity < 0.0001 )
           fprintf(summary,    "%1.3f *  %s\n", ((double)passCount/sampleSize), testNames[test]);
        else
           fprintf(summary,    "%1.3f    %s\n", ((double)passCount/sampleSize), testNames[test]);
	
	fclose(fp);
	free(A);
	
	return sampleSize;
}
