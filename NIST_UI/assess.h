#include "../sourse_nist/include/defs.h"
//#include "../sourse_nist/include/decls.h"
#include <string>

using namespace std;

public class InitNISTParam
{
public:
    //InitNISTParam() {}
    ~InitNISTParam()
    {
       delete _inpuFileName;
       delete _statisticalTestVector;
    }

    void SetN(int n)
    { _parametersOfNIST.n = n; }

	void SetBlockFrequencyBlockLength(int blockFrequencyBlockLength)
    { _parametersOfNIST.blockFrequencyBlockLength = blockFrequencyBlockLength; }

	void SetNonOverlappingTemplateBlockLength(int nonOverlappingTemplateBlockLength)
    { _parametersOfNIST.nonOverlappingTemplateBlockLength = nonOverlappingTemplateBlockLength; }

	void SetOverlappingTemplateBlockLength(int overlappingTemplateBlockLength)
    { _parametersOfNIST.overlappingTemplateBlockLength = overlappingTemplateBlockLength; }

	void SetApproximateEntropyBlockLength(int approximateEntropyBlockLength)
    { _parametersOfNIST.approximateEntropyBlockLength = approximateEntropyBlockLength; }

	void SetSerialBlockLength(int serialBlockLength)
    { _parametersOfNIST.serialBlockLength = serialBlockLength; }

	void SetLinearComplexitySequenceLength(int linearComplexitySequenceLength)
    { _parametersOfNIST.linearComplexitySequenceLength = linearComplexitySequenceLength; }

	void SetNumOfBitStreams(int numOfBitStreams)
    { _parametersOfNIST.numOfBitStreams = numOfBitStreams; }

    void SetInputFileName(char* fileName)
    { _inpuFileName = fileName; }

    char* GetInputFileName()
    { return _inpuFileName; }

    void SetReadFileMode(int mode)
    { _readFileMode = mode; }

    int GetReadFileMode()
    { return _readFileMode; }

   void SetGenertorSelectionIndex(int index)
    { _genertorSelectionIndex = index; }

    int GetGenertorSelectionIndex()
    { return _genertorSelectionIndex; }

    void SetStatisticalTestVector(int* statisticalTestVector)
    { _statisticalTestVector = statisticalTestVector; }

    int* GetStatisticalTestVector()
    { return _statisticalTestVector; }

    void CopyParam(_testParameters& copyPar)
    {
       copyPar.n = _parametersOfNIST.n;
	   copyPar.blockFrequencyBlockLength = _parametersOfNIST.blockFrequencyBlockLength;
	   copyPar.nonOverlappingTemplateBlockLength = _parametersOfNIST.nonOverlappingTemplateBlockLength;
	   copyPar.overlappingTemplateBlockLength = _parametersOfNIST.overlappingTemplateBlockLength;
	   copyPar.approximateEntropyBlockLength = _parametersOfNIST.approximateEntropyBlockLength;
	   copyPar.serialBlockLength = _parametersOfNIST.serialBlockLength;
	   copyPar.linearComplexitySequenceLength = _parametersOfNIST.linearComplexitySequenceLength;
	   copyPar.numOfBitStreams = _parametersOfNIST.numOfBitStreams;
    }

    int GetProgress()
    {
        return progerss;
    }

    void incProgress()
    {
       progerss++;
    }

    void ResetProgress()
    {
        progerss = 0;
    }

	//викликати після ініціалізації всіх параметрів;
	int GetMaxProgress()
	{
		return _parametersOfNIST.numOfBitStreams + 20;
	}

	string  GetCulture()
	{
		return _culture;
	}

	void SetCulture(string culture)
	{
	  _culture = culture;
	}

private:
    _testParameters _parametersOfNIST;
     char* _inpuFileName;
     int _readFileMode;
     int _genertorSelectionIndex;
     int* _statisticalTestVector;
     int progerss;
	 string  _culture;
};

void	partitionResultFile(int numOfFiles, int numOfSequences, int option, int testNameID);
void	postProcessResults(int option, InitNISTParam*);
int		cmp(const double *a, const double *b);
int		computeMetrics(char *s, int test);
char*   NIST_Main(InitNISTParam*); 