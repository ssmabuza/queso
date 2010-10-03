//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// QUESO - a library to support the Quantification of Uncertainty
// for Estimation, Simulation and Optimization
//
// Copyright (C) 2008,2009,2010 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, 
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
// 
// $Id$
//
//--------------------------------------------------------------------------

#ifndef __UQ_SCALAR_SEQUENCE_H__
#define __UQ_SCALAR_SEQUENCE_H__

#include <uqFft.h>
#include <uqOneDGrid.h>
#include <uqEnvironment.h>
#include <uqMiscellaneous.h>
#include <uqDefines.h>
#include <vector>
#include <complex>
#include <gsl/gsl_randist.h>

#define SCALAR_SEQUENCE_INIT_MPI_MSG 1
#define SCALAR_SEQUENCE_SIZE_MPI_MSG 1
#define SCALAR_SEQUENCE_DATA_MPI_MSG 1

template <class T>
class uqScalarSequenceClass
{
public:
  typedef typename std::vector<T>::iterator       seqScalarPositionIteratorTypedef;
  typedef typename std::vector<T>::const_iterator seqScalarPositionConstIteratorTypedef;
  uqScalarSequenceClass(const uqBaseEnvironmentClass& env,
                              unsigned int subSequenceSize,
                        const std::string& name);
 ~uqScalarSequenceClass();

  uqScalarSequenceClass<T>& operator= (const uqScalarSequenceClass<T>& rhs);

  const uqBaseEnvironmentClass& env               () const;
  const std::string& name                         () const;
        void         setName                      (const std::string& newName);
        void         clear                        ();
        unsigned int subSequenceSize              () const;
        unsigned int unifiedSequenceSize          (bool useOnlyInter0Comm) const;
        void         resizeSequence               (unsigned int newSequenceSize);
        void         resetValues                  (unsigned int initialPos, unsigned int numPos);
        void         erasePositions               (unsigned int initialPos, unsigned int numPos);
  const T&           operator[]                   (unsigned int posId) const;
        T&           operator[]                   (unsigned int posId);
        void         getUnifiedContentsAtProc0Only(bool useOnlyInter0Comm,
                                                   std::vector<T>& outputVec) const;
        void         setGaussian                  (const gsl_rng* rng, const T& mean, const T& stdDev);
        void         setUniform                   (const gsl_rng* rng, const T& a,    const T& b     );
        void         subUniformlySampledMdf       (unsigned int                    numIntervals,
                                                   T&                              minDomainValue,
                                                   T&                              maxDomainValue,
                                                   std::vector<T>&                 mdfValues) const;
        void         subUniformlySampledCdf       (unsigned int                    numIntervals,
                                                   T&                              minDomainValue,
                                                   T&                              maxDomainValue,
                                                   std::vector<T>&                 cdfValues) const;
        void         unifiedUniformlySampledCdf   (bool                            useOnlyInter0Comm,
                                                   unsigned int                    numIntervals,
                                                   T&                              unifiedMinDomainValue,
                                                   T&                              unifiedMaxDomainValue,
                                                   std::vector<T>&                 unifiedCdfValues) const;
        void         subBasicCdf                  (unsigned int                    numIntervals,
                                                   uqUniformOneDGridClass<T>*&     gridValues,
                                                   std::vector<T>&                 cdfValues) const;
        void         subWeigthCdf                 (unsigned int                    numIntervals,
                                                   uqUniformOneDGridClass<T>*&     gridValues,
                                                   std::vector<T>&                 cdfValues) const;

        T            subMean                      (unsigned int                    initialPos,
                                                   unsigned int                    numPos) const;
        T            unifiedMean                  (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    localNumPos) const;
        T            subMeanCltStd                (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   const T&                        meanValue) const;
        T            unifiedMeanCltStd            (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    localNumPos,
                                                   const T&                        unifiedMeanValue) const;
        T            subSampleVariance            (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   const T&                        meanValue) const;
        T            unifiedSampleVariance        (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    localNumPos,
                                                   const T&                        unifiedMeanValue) const;
        T            subPopulationVariance        (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   const T&                        meanValue) const;
        T            unifiedPopulationVariance    (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   const T&                        unifiedMeanValue) const;
        T            autoCovariance               (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   const T&                        meanValue,
                                                   unsigned int                    lag) const;
        T            autoCorrViaDef               (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   unsigned int                    lag) const;
        void         autoCorrViaFft               (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   unsigned int                    maxLag,
                                                   std::vector<T>&                 autoCorrs) const;
        void         autoCorrViaFft               (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   unsigned int                    numSum,
                                                   T&                              autoCorrsSum) const;
        T            bmm                          (unsigned int                    initialPos,
                                                   unsigned int                    batchLength) const;
        void         psd                          (unsigned int                    initialPos,
                                                   unsigned int                    numBlocks,
                                                   double                          hopSizeRatio,
                                                   std::vector<double>&            psdSequence) const;
        T            geweke                       (unsigned int                    initialPos,
                                                   double                          ratioNa,
                                                   double                          ratioNb) const;
        T            meanStacc                    (unsigned int                    initialPos) const;
        void         subMinMax                    (unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   T&                              minValue,
                                                   T&                              maxValue) const;
        void         unifiedMinMax                (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    numPos,
                                                   T&                              unifiedMinValue,
                                                   T&                              unifiedMaxValue) const;
        void         subHistogram                 (unsigned int                    initialPos,
                                                   const T&                        minHorizontalValue,
                                                   const T&                        maxHorizontalValue,
                                                   std::vector<T>&                 centers,
                                                   std::vector<unsigned int>&      bins) const;
        void         unifiedHistogram             (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   const T&                        unifiedMinHorizontalValue,
                                                   const T&                        unifiedMaxHorizontalValue,
                                                   std::vector<T>&                 unifiedCenters,
                                                   std::vector<unsigned int>&      unifiedBins) const;
        void         subBasicHistogram            (unsigned int                    initialPos,
                                                   const T&                        minHorizontalValue,
                                                   const T&                        maxHorizontalValue,
                                                   uqUniformOneDGridClass<T>*&     gridValues,
                                                   std::vector<unsigned int>&      bins) const;
        void         subWeigthHistogram           (unsigned int                    initialPos,
                                                   const T&                        minHorizontalValue,
                                                   const T&                        maxHorizontalValue,
                                                   uqUniformOneDGridClass<T>*&     gridValues,
                                                   std::vector<unsigned int>&      bins) const;
        void         subCdfStacc                  (unsigned int                    initialPos,
                                                   std::vector<double>&            cdfStaccValues,
                                                   std::vector<double>&            cdfStaccValuesup,
                                                   std::vector<double>&            cdfStaccValueslow,
                                                   const uqScalarSequenceClass<T>& sortedDataValues) const;
        void         subCdfStacc                  (unsigned int                    initialPos,
                                                   const std::vector<T>&           evaluationPositions,
                                                   std::vector<double>&            cdfStaccValues) const;
        void         subSort                      (unsigned int                    initialPos,
                                                   uqScalarSequenceClass<T>&       sortedSequence) const;
        void         unifiedSort                  (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   uqScalarSequenceClass<T>&       unifiedSortedSequence) const;
        T            subInterQuantileRange        (unsigned int                    initialPos) const;
        T            unifiedInterQuantileRange    (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos) const;
        T            subScaleForKde               (unsigned int                    initialPos,
                                                   const T&                        iqrValue,
                                                   unsigned int                    kdeDimension) const;
        T            unifiedScaleForKde           (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   const T&                        unifiedIqrValue,
                                                   unsigned int                    kdeDimension) const;
        void         subGaussian1dKde             (unsigned int                    initialPos,
                                                   double                          scaleValue,
                                                   const std::vector<T>&           evaluationPositions,
                                                   std::vector<double>&            densityValues) const;
        void         unifiedGaussian1dKde         (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   double                          unifiedScaleValue,
                                                   const std::vector<T>&           unifiedEvaluationPositions,
                                                   std::vector<double>&            unifiedDensityValues) const;

        void         filter                       (unsigned int                    initialPos,
                                                   unsigned int                    spacing);

        T            brooksGelmanConvMeasure      (bool                            useOnlyInter0Comm,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    spacing) const;

        void         append                       (const uqScalarSequenceClass<T>& src,
                                                   unsigned int                    initialPos,
                                                   unsigned int                    numPos);

        void         subWriteContents             (const std::string&              fileName,
                                                   const std::string&              fileType,
                                                   const std::set<unsigned int>&   allowedSubEnvIds) const;
        void         subWriteContents             (std::ofstream&                  ofs,
                                                   const std::string&              fileType) const;
        void         unifiedWriteContents         (const std::string&              fileName,
                                                   const std::string&              fileType) const;
private:
        void         copy                         (const uqScalarSequenceClass<T>& src);
        void         extractScalarSeq             (unsigned int                    initialPos,
                                                   unsigned int                    spacing,
                                                   unsigned int                    numPos,
                                                   uqScalarSequenceClass<T>&       scalarSeq) const;
        void         extractRawData               (unsigned int                    initialPos,
                                                   unsigned int                    spacing,
                                                   unsigned int                    numPos,
                                                   std::vector<double>&            rawData) const;
	std::vector<T>& rawData                   ();
        void         subSort                      ();
        void         parallelMerge                (std::vector<T>&                 sortedBuffer,
                                                   const std::vector<T>&           leafData,
                                                   unsigned int                    treeLevel) const;

  const uqBaseEnvironmentClass& m_env;
  std::string                   m_name;
  std::vector<T>                m_seq;
};

template <class T>
uqScalarSequenceClass<T>::uqScalarSequenceClass(
  const uqBaseEnvironmentClass& env,
        unsigned int            subSequenceSize,
  const std::string&            name)
  :
  m_env (env),
  m_name(name),
  m_seq (subSequenceSize,0.)
{
}

template <class T>
uqScalarSequenceClass<T>::~uqScalarSequenceClass()
{
}

template <class T>
uqScalarSequenceClass<T>&
uqScalarSequenceClass<T>::operator= (const uqScalarSequenceClass<T>& rhs)
{
  this->copy(rhs);
  return *this;
}

template <class T>
void
uqScalarSequenceClass<T>::copy(const uqScalarSequenceClass<T>& src)
{
  m_name = src.m_name;
  m_seq.clear();
  m_seq.resize(src.subSequenceSize(),0.);
  for (unsigned int i = 0; i < m_seq.size(); ++i) {
    m_seq[i] = src.m_seq[i];
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::filter(
  unsigned int initialPos,
  unsigned int spacing)
{
  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "Entering uqScalarSequenceClass<V,M>::filter()"
                            << ": initialPos = "      << initialPos
                            << ", spacing = "         << spacing
                            << ", subSequenceSize = " << this->subSequenceSize()
                            << std::endl;
  }

  unsigned int i = 0;
  unsigned int j = initialPos;
  unsigned int originalSubSequenceSize = this->subSequenceSize();
  while (j < originalSubSequenceSize) {
    if (i != j) {
      //*m_env.subDisplayFile() << i << "--" << j << " ";
      m_seq[i] = m_seq[j];
    }
    i++;
    j += spacing;
  }

  this->resizeSequence(i);

  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "Leaving uqScalarSequenceClass<V,M>::filter()"
                            << ": initialPos = "      << initialPos
                            << ", spacing = "         << spacing
                            << ", subSequenceSize = " << this->subSequenceSize()
                            << std::endl;
  }

  return;
}

template <class T>
T
uqScalarSequenceClass<T>::brooksGelmanConvMeasure(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  unsigned int spacing) const
{
  double resultValue = 0.;

  // FIX ME: put logic if (numSubEnvs == 1) ...

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      UQ_FATAL_TEST_MACRO(true,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::brooksGelmanConvMeasure()",
                          "not implemented yet");
    }
    else {
      // Node not in the 'inter0' communicator
      // Do nothing
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::brooksGelmanConvMeasure()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return resultValue;
}

template <class T>
void
uqScalarSequenceClass<T>::append(
  const uqScalarSequenceClass<T>& src,
  unsigned int                    initialPos,
  unsigned int                    numPos)
{
  UQ_FATAL_TEST_MACRO((src.subSequenceSize() < (initialPos+1)),
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::append()",
                      "initialPos is too big");

  UQ_FATAL_TEST_MACRO((src.subSequenceSize() < (initialPos+numPos)),
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::append()",
                      "numPos is too big");

  unsigned int currentSize = this->subSequenceSize();
  m_seq.resize(currentSize+numPos,0.);
  for (unsigned int i = 0; i < numPos; ++i) {
    m_seq[currentSize+i] = src.m_seq[initialPos+i];
  }

  return;
}

template <class T>
const uqBaseEnvironmentClass&
uqScalarSequenceClass<T>::env() const
{
  return m_env;
}

template <class T>
const std::string&
uqScalarSequenceClass<T>::name() const
{
  return m_name;
}

template <class T>
void
uqScalarSequenceClass<T>::setName(const std::string& newName)
{
  m_name = newName;
  return;
}

template <class T>
void
uqScalarSequenceClass<T>::clear()
{
  unsigned int numPos = this->subSequenceSize();
  if (numPos) {
    this->resetValues(0,numPos);
    this->resizeSequence(0);
  }

 return;
}

template <class T>
unsigned int
uqScalarSequenceClass<T>::subSequenceSize() const
{
  return m_seq.size();
}

template <class T>
unsigned int
uqScalarSequenceClass<T>::unifiedSequenceSize(bool useOnlyInter0Comm) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subSequenceSize();
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  unsigned int unifiedNumSamples = 0;
  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      unsigned int subNumSamples = this->subSequenceSize();
      int mpiRC = MPI_Allreduce((void *) &subNumSamples, (void *) &unifiedNumSamples, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSequenceSize()",
                          "failed MPI_Allreduce() for unifiedSequenceSize()");
    }
    else {
      // Node not in the 'inter0' communicator
      unifiedNumSamples = this->subSequenceSize();
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedSequenceSize()",
                        "parallel vectors not supported yet");
  }

  return unifiedNumSamples;
}

template <class T>
void
uqScalarSequenceClass<T>::resizeSequence(unsigned int newSequenceSize)
{
  if (newSequenceSize != this->subSequenceSize()) {
    m_seq.resize(newSequenceSize,0.);
    std::vector<T>(m_seq).swap(m_seq);
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::resetValues(unsigned int initialPos, unsigned int numPos)
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequences<T>::resetValues()",
                      "invalid input data");

  for (unsigned int j = 0; j < numPos; ++j) {
    m_seq[initialPos+j] = 0.;
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::erasePositions(unsigned int initialPos, unsigned int numPos)
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequences<T>::erasePositions()",
                      "invalid input data");

  seqScalarPositionIteratorTypedef posIteratorBegin = m_seq.begin();
  if (initialPos < this->subSequenceSize()) std::advance(posIteratorBegin,initialPos);
  else                                      posIteratorBegin = m_seq.end();

  unsigned int posEnd = initialPos + numPos - 1;
  seqScalarPositionIteratorTypedef posIteratorEnd = m_seq.begin();
  if (posEnd < this->subSequenceSize()) std::advance(posIteratorEnd,posEnd);
  else                                  posIteratorEnd = m_seq.end();

  unsigned int oldSequenceSize = this->subSequenceSize();
  m_seq.erase(posIteratorBegin,posIteratorEnd);
  UQ_FATAL_TEST_MACRO((oldSequenceSize - numPos) != this->subSequenceSize(),
                      m_env.worldRank(),
                      "uqScalarSequences<T>::erasePositions()",
                      "(oldSequenceSize - numPos) != this->subSequenceSize()");

  return;
}

template <class T>
const T&
uqScalarSequenceClass<T>::operator[](unsigned int posId) const
{
  if (posId >= this->subSequenceSize()) {
    std::cerr << "In uqScalarSequenceClass<T>::operator[]() const"
              << ": posId = "                   << posId
              << ", this->subSequenceSize() = " << this->subSequenceSize()
              << std::endl;
  }
  UQ_FATAL_TEST_MACRO((posId >= this->subSequenceSize()),
                      m_env.worldRank(),
                      "uqScalarSequences<T>::operator[] const",
                      "posId > subSequenceSize()");

  return m_seq[posId];
}

template <class T>
T&
uqScalarSequenceClass<T>::operator[](unsigned int posId)
{
  if (posId >= this->subSequenceSize()) {
    std::cerr << "In uqScalarSequenceClass<T>::operator[]()"
              << ": posId = "                   << posId
              << ", this->subSequenceSize() = " << this->subSequenceSize()
              << std::endl;
  }
  UQ_FATAL_TEST_MACRO((posId >= this->subSequenceSize()),
                      m_env.worldRank(),
                      "uqScalarSequences<T>::operator[]",
                      "posId > subSequenceSize()");

  return m_seq[posId];
}

template <class T>
void
uqScalarSequenceClass<T>::getUnifiedContentsAtProc0Only(
  bool useOnlyInter0Comm,
  std::vector<T>& outputVec) const
{
  // The logic (numSubEnvs == 1) does *not* apply here because 'outputVec' needs to be filled
  //if (m_env.numSubEnvironments() == 1) {
  //  // No need to do anything
  //  return;
  //}

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      int auxSubSize = (int) this->subSequenceSize();
      unsigned int auxUnifiedSize = this->unifiedSequenceSize(useOnlyInter0Comm);
      outputVec.resize(auxUnifiedSize,0.);

      //******************************************************************
      // Use MPI_Gatherv for the case different nodes have different amount of data // KAUST4
      //******************************************************************

      //int MPI_Gather (void *sendbuf, int sendcnt, MPI_Datatype sendtype, 
      //                void *recvbuf, int recvcount, MPI_Datatype recvtype, 
      //                int root, MPI_Comm comm )
      std::vector<int> recvcnts(m_env.inter0Comm().NumProc(),0); // '0' is NOT the correct value for recvcnts[0]
      int mpiRC = MPI_Gather((void *) &auxSubSize, 1, MPI_INT, (void *) &recvcnts[0], (int) 1, MPI_INT, 0, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::getUnifiedContentsAtProc0Only()",
                          "failed MPI_Gather()");
      if (m_env.inter0Rank() == 0) {
        //recvcnts[0] = (int) this->subSequenceSize(); // FIX ME: really necessary????
        UQ_FATAL_TEST_MACRO(recvcnts[0] != (int) this->subSequenceSize(),
                            m_env.worldRank(),
                            "uqScalarSequenceClass<T>::getUnifiedContentsAtProc0Only()",
                            "failed MPI_Gather() result at proc 0");
      }

      std::vector<int> displs(m_env.inter0Comm().NumProc(),0);
      for (unsigned int r = 1; r < (unsigned int) m_env.inter0Comm().NumProc(); ++r) { // Yes, from '1' on
        displs[r] = displs[r-1] + recvcnts[r-1];
      }

#if 0 // for debug only
      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        for (unsigned int r = 0; r < (unsigned int) m_env.inter0Comm().NumProc(); ++r) {
          *m_env.subDisplayFile() << "  auxSubSize = "            << auxSubSize
                                  << ", recvcnts[" << r << "] = " << recvcnts[r]
                                  << ", displs["   << r << "] = " << displs[r]
                                  << ", m_seq.size() = "          << m_seq.size()
                                  << ", outputVec.size() = "      << outputVec.size()
                                  << std::endl;
        }
        for (unsigned int i = 0; i < m_seq.size(); ++i) {
          *m_env.subDisplayFile() << "  (before gatherv) m_seq[" << i << "]= " << m_seq[i]
                                  << std::endl;
        }
      }
#endif

      //int MPI_Gatherv(void *sendbuf, int sendcnt, MPI_Datatype sendtype, 
      //                void *recvbuf, int *recvcnts, int *displs, MPI_Datatype recvtype, 
      //                int root, MPI_Comm comm )
      mpiRC = MPI_Gatherv((void *) &m_seq[0], auxSubSize, MPI_DOUBLE, (void *) &outputVec[0], (int *) &recvcnts[0], (int *) &displs[0], MPI_DOUBLE, 0, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::getUnifiedContentsAtProc0Only()",
                          "failed MPI_Gatherv()");

#if 0 // for debug only
      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        for (unsigned int i = 0; i < m_seq.size(); ++i) {
          *m_env.subDisplayFile() << "  (after gatherv) m_seq[" << i << "]= " << m_seq[i]
                                  << std::endl;
        }
        for (unsigned int i = 0; i < outputVec.size(); ++i) {
          *m_env.subDisplayFile() << "  (after gatherv) outputVec[" << i << "]= " << outputVec[i]
                                  << std::endl;
        }
      }
#endif

#if 0 // for debug only
      if (m_env.inter0Rank() == 0) {
        for (unsigned int i = 0; i < auxSubSize; ++i) {
          outputVec[i] = m_seq[i];
        }
        mpiRC = MPI_Gatherv(MPI_IN_PLACE, auxSubSize, MPI_DOUBLE, (void *) &outputVec[0], (int *) &recvcnts[0], (int *) &displs[0], MPI_DOUBLE, 0, m_env.inter0Comm().Comm());
      }
      else {
        mpiRC = MPI_Gatherv((void *) &m_seq[0], auxSubSize, MPI_DOUBLE, (void *) &outputVec[0], (int *) &recvcnts[0], (int *) &displs[0], MPI_DOUBLE, 0, m_env.inter0Comm().Comm());
      }
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::getUnifiedContentsAtProc0Only()",
                          "failed MPI_Gatherv()");
      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        for (unsigned int i = 0; i < m_seq.size(); ++i) {
          *m_env.subDisplayFile() << "  (after 2nd gatherv) m_seq[" << i << "]= " << m_seq[i]
                                  << std::endl;
        }
        for (unsigned int i = 0; i < outputVec.size(); ++i) {
          *m_env.subDisplayFile() << "  (after 2nd gatherv) outputVec[" << i << "]= " << outputVec[i]
                                  << std::endl;
        }
      }
#endif
    }
    else {
      // Node not in the 'inter0' communicator
      // No need to do anything
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::getUnifiedContentsAtProc0Only()",
                        "parallel vectors not supported yet");
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::setGaussian(const gsl_rng* rng, const T& meanValue, const T& stdDev)
{
  unsigned int maxJ = this->subSequenceSize();
  if (meanValue == 0.) {
    for (unsigned int j = 0; j < maxJ; ++j) {
      m_seq[j] = gsl_ran_gaussian(rng,stdDev);
    }
  }
  else {
    for (unsigned int j = 0; j < maxJ; ++j) {
      m_seq[j] = meanValue + gsl_ran_gaussian(rng,stdDev);
    }
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::setUniform(const gsl_rng* rng, const T& a, const T& b)
{
  unsigned int maxJ = this->subSequenceSize();
  if (a == 0.) {
    if (b == 1.) {
      for (unsigned int j = 0; j < maxJ; ++j) {
        m_seq[j] = gsl_rng_uniform(rng);
      }
    }
    else {
      for (unsigned int j = 0; j < maxJ; ++j) {
        m_seq[j] = b*gsl_rng_uniform(rng);
      }
    }
  }
  else {
    if ((b-a) == 1.) {
      for (unsigned int j = 0; j < maxJ; ++j) {
        m_seq[j] = a + gsl_rng_uniform(rng);
      }
    }
    else {
      for (unsigned int j = 0; j < maxJ; ++j) {
        m_seq[j] = a + (b-a)*gsl_rng_uniform(rng);
      }
    }
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subUniformlySampledMdf(
  unsigned int    numEvaluationPoints,
  T&              minDomainValue,
  T&              maxDomainValue,
  std::vector<T>& mdfValues) const
{
  T                         tmpMinValue;
  T                         tmpMaxValue;
  std::vector<T>            centers(numEvaluationPoints,0.);
  std::vector<unsigned int> bins   (numEvaluationPoints,0);

  subMinMax(0, // initialPos
            this->subSequenceSize(),
            tmpMinValue,
            tmpMaxValue);
  subHistogram(0, // initialPos,
               tmpMinValue,
               tmpMaxValue,
               centers,
               bins);

  minDomainValue = centers[0];
  maxDomainValue = centers[centers.size()-1];
  T binSize = (maxDomainValue - minDomainValue)/((double)(centers.size() - 1));

  unsigned int totalCount = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    totalCount += bins[i];
  }

  mdfValues.clear();
  mdfValues.resize(numEvaluationPoints);
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    mdfValues[i] = ((T) bins[i])/((T) totalCount)/binSize;
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subUniformlySampledCdf(
  unsigned int    numEvaluationPoints,
  T&              minDomainValue,
  T&              maxDomainValue,
  std::vector<T>& cdfValues) const
{
  T                         tmpMinValue;
  T                         tmpMaxValue;
  std::vector<T>            centers(numEvaluationPoints,0.);
  std::vector<unsigned int> bins   (numEvaluationPoints,0);

  subMinMax(0, // initialPos
            this->subSequenceSize(),
            tmpMinValue,
            tmpMaxValue);
  subHistogram(0, // initialPos,
               tmpMinValue,
               tmpMaxValue,
               centers,
               bins);

  minDomainValue = centers[0];
  maxDomainValue = centers[centers.size()-1];

  unsigned int sumOfBins = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    sumOfBins += bins[i];
  }

  cdfValues.clear();
  cdfValues.resize(numEvaluationPoints);
  unsigned int partialSum = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    partialSum += bins[i];
    cdfValues[i] = ((T) partialSum)/((T) sumOfBins);
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::unifiedUniformlySampledCdf(
  bool            useOnlyInter0Comm,
  unsigned int    numEvaluationPoints,
  T&              unifiedMinDomainValue,
  T&              unifiedMaxDomainValue,
  std::vector<T>& unifiedCdfValues) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subUniformlySampledCdf(numEvaluationPoints,
                                        unifiedMinDomainValue,
                                        unifiedMaxDomainValue,
                                        unifiedCdfValues);
  }

  // KAUST2
  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        *m_env.subDisplayFile() << "Entering uqScalarSequenceClass<T>::unifiedUniformlySampledCdf()"
                                << std::endl;
      }

      T                         unifiedTmpMinValue;
      T                         unifiedTmpMaxValue;
      std::vector<T>            unifiedCenters(numEvaluationPoints,0.);
      std::vector<unsigned int> unifiedBins   (numEvaluationPoints,0);

      this->unifiedMinMax(useOnlyInter0Comm,
                          0, // initialPos
                          this->subSequenceSize(),
                          unifiedTmpMinValue,
                          unifiedTmpMaxValue);
      this->unifiedHistogram(useOnlyInter0Comm,
                             0, // initialPos
                             unifiedTmpMinValue,
                             unifiedTmpMaxValue,
                             unifiedCenters,
                             unifiedBins);

      unifiedMinDomainValue = unifiedCenters[0];
      unifiedMaxDomainValue = unifiedCenters[unifiedCenters.size()-1];

      unsigned int unifiedTotalSumOfBins = 0;
      for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
        unifiedTotalSumOfBins += unifiedBins[i];
      }

      std::vector<unsigned int> unifiedPartialSumsOfBins(numEvaluationPoints,0);
      unifiedPartialSumsOfBins[0] = unifiedBins[0];
      for (unsigned int i = 1; i < numEvaluationPoints; ++i) { // Yes, from '1'
        unifiedPartialSumsOfBins[i] = unifiedPartialSumsOfBins[i-1] + unifiedBins[i];
      }

      unifiedCdfValues.clear();
      unifiedCdfValues.resize(numEvaluationPoints);
      for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
        unifiedCdfValues[i] = ((T) unifiedPartialSumsOfBins[i])/((T) unifiedTotalSumOfBins);
      }

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
          *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedUniformlySampledCdf()"
                                  << ": i = " << i
                                  << ", unifiedTmpMinValue = "       << unifiedTmpMinValue
                                  << ", unifiedTmpMaxValue = "       << unifiedTmpMaxValue
                                  << ", unifiedBins = "              << unifiedBins[i]
                                  << ", unifiedCdfValue = "          << unifiedCdfValues[i]
                                  << ", unifiedPartialSumsOfBins = " << unifiedPartialSumsOfBins[i]
                                  << ", unifiedTotalSumOfBins = "    << unifiedTotalSumOfBins
                                  << std::endl;
        }
      }

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        *m_env.subDisplayFile() << "Leaving uqScalarSequenceClass<T>::unifiedUniformlySampledCdf()"
                                << std::endl;
      }
    }
    else {
      // Node not in the 'inter0' communicator
      this->subUniformlySampledCdf(numEvaluationPoints,
                                   unifiedMinDomainValue,
                                   unifiedMaxDomainValue,
                                   unifiedCdfValues);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedUniformlySampledCdf()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subBasicCdf(
  unsigned int                numEvaluationPoints,
  uqUniformOneDGridClass<T>*& gridValues,
  std::vector<T>&             cdfValues) const
{
  T                         tmpMinValue;
  T                         tmpMaxValue;
  std::vector<unsigned int> bins(numEvaluationPoints,0);

  subMinMax(0, // initialPos
            this->subSequenceSize(),
            tmpMinValue,
            tmpMaxValue);
  subBasicHistogram(0, // initialPos,
                    tmpMinValue,
                    tmpMaxValue,
                    gridValues,
                    bins);

  unsigned int sumOfBins = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    sumOfBins += bins[i];
  }

  cdfValues.clear();
  cdfValues.resize(numEvaluationPoints);
  unsigned int partialSum = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    partialSum += bins[i];
    cdfValues[i] = ((T) partialSum)/((T) sumOfBins);
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subWeigthCdf(
  unsigned int                numEvaluationPoints,
  uqUniformOneDGridClass<T>*& gridValues,
  std::vector<T>&             cdfValues) const
{
  T                         tmpMinValue;
  T                         tmpMaxValue;
  std::vector<unsigned int> bins(numEvaluationPoints,0);

  subMinMax(0, // initialPos
            this->subSequenceSize(),
            tmpMinValue,
            tmpMaxValue);
  subWeigthHistogram(0, // initialPos,
                     tmpMinValue,
                     tmpMaxValue,
                     gridValues,
                     bins);

  unsigned int sumOfBins = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    sumOfBins += bins[i];
  }

  cdfValues.clear();
  cdfValues.resize(numEvaluationPoints);
  unsigned int partialSum = 0;
  for (unsigned int i = 0; i < numEvaluationPoints; ++i) {
    partialSum += bins[i];
    cdfValues[i] = ((T) partialSum)/((T) sumOfBins);
  }

  return;
}

template <class T>
T
uqScalarSequenceClass<T>::subMean(
  unsigned int initialPos,
  unsigned int numPos) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subMean()",
                      "invalid input data");

  unsigned int finalPosPlus1 = initialPos + numPos;
  T tmpSum = 0.;
  for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
    tmpSum += m_seq[j];
  }

  return tmpSum/(T) numPos;
}

template <class T>
T
uqScalarSequenceClass<T>::unifiedMean(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  unsigned int numPos) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subMean(initialPos,
                         numPos);
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  T unifiedMeanValue = 0.;
  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      bool bRC = ((initialPos          <  this->subSequenceSize()) &&
                  (0                   <  numPos                 ) &&
                  ((initialPos+numPos) <= this->subSequenceSize()));
      UQ_FATAL_TEST_MACRO(bRC == false,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMean()",
                          "invalid input data");

      unsigned int finalPosPlus1 = initialPos + numPos;
      T localSum = 0.;
      for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
        localSum += m_seq[j];
      }

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedMean()"
                                << ": initialPos = " << initialPos
                                << ", numPos = "     << numPos
                                << ", before MPI_Allreduce"
                                << std::endl;
      }
      //std::cout << m_env.inter0Comm().MyPID()
      //          << std::endl;
      //sleep(1);
      unsigned int unifiedNumPos = 0;
      int mpiRC = MPI_Allreduce((void *) &numPos, (void *) &unifiedNumPos, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMean()",
                          "failed MPI_Allreduce() for numPos");

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedMean()"
                                << ": numPos = "        << numPos
                                << ", unifiedNumPos = " << unifiedNumPos
                                << std::endl;
      }

      mpiRC = MPI_Allreduce((void *) &localSum, (void *) &unifiedMeanValue, (int) 1, MPI_DOUBLE, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMean()",
                          "failed MPI_Allreduce() for sum");

      unifiedMeanValue /= ((T) unifiedNumPos);

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedMean()"
                                << ": localSum = "         << localSum
                                << ", unifiedMeanValue = " << unifiedMeanValue
                                << std::endl;
      }
    }
    else {
      // Node not in the 'inter0' communicator
      this->subMean(initialPos,
                    numPos);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedMean()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return unifiedMeanValue;
}

template <class T>
T
uqScalarSequenceClass<T>::subMeanCltStd(
  unsigned int initialPos,
  unsigned int numPos,
  const T&     meanValue) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subMeanCltStd()",
                      "invalid input data");

  unsigned int finalPosPlus1 = initialPos + numPos;
  T diff;
  T stdValue = 0.;
  for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
    diff = m_seq[j] - meanValue;
    stdValue += diff*diff;
  }

  stdValue /= (((T) numPos) - 1.);
  stdValue /= (((T) numPos) - 1.);
  stdValue = sqrt(stdValue);

  return stdValue;
}

template <class T>
T
uqScalarSequenceClass<T>::unifiedMeanCltStd(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  unsigned int numPos,
  const T&     unifiedMeanValue) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subMeanCltStd(initialPos,
                               numPos,
                               unifiedMeanValue);
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  T unifiedStdValue = 0.;
  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      bool bRC = ((initialPos          <  this->subSequenceSize()) &&
                  (0                   <  numPos                 ) &&
                  ((initialPos+numPos) <= this->subSequenceSize()));
      UQ_FATAL_TEST_MACRO(bRC == false,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMeanCltStd()",
                          "invalid input data");

      unsigned int finalPosPlus1 = initialPos + numPos;
      T diff;
      T localStdValue = 0.;
      for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
        diff = m_seq[j] - unifiedMeanValue;
        localStdValue += diff*diff;
      }

      unsigned int unifiedNumPos = 0;
      int mpiRC = MPI_Allreduce((void *) &numPos, (void *) &unifiedNumPos, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMeanCltStd()",
                          "failed MPI_Allreduce() for numPos");

      mpiRC = MPI_Allreduce((void *) &localStdValue, (void *) &unifiedStdValue, (int) 1, MPI_DOUBLE, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMeanCltStd()",
                          "failed MPI_Allreduce() for stdValue");

      unifiedStdValue /= (((T) unifiedNumPos) - 1.);
      unifiedStdValue /= (((T) unifiedNumPos) - 1.);
      unifiedStdValue /= sqrt(unifiedStdValue);
    }
    else {
      // Node not in the 'inter0' communicator
      this->subMeanCltStd(initialPos,
                          numPos,
                          unifiedMeanValue);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedMeanCltStd()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return unifiedStdValue;
}

template <class T>
T
uqScalarSequenceClass<T>::subSampleVariance(
  unsigned int initialPos,
  unsigned int numPos,
  const T&     meanValue) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subSampleVariance()",
                      "invalid input data");

  unsigned int finalPosPlus1 = initialPos + numPos;
  T diff;
  T samValue = 0.;
  for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
    diff = m_seq[j] - meanValue;
    samValue += diff*diff;
  }

  samValue /= (((T) numPos) - 1.);

  return samValue;
}

template <class T>
T
uqScalarSequenceClass<T>::unifiedSampleVariance(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  unsigned int numPos,
  const T&     unifiedMeanValue) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subSampleVariance(initialPos,
                                   numPos,
                                   unifiedMeanValue);
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  T unifiedSamValue = 0.;
  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      bool bRC = ((initialPos          <  this->subSequenceSize()) &&
                  (0                   <  numPos                 ) &&
                  ((initialPos+numPos) <= this->subSequenceSize()));
      UQ_FATAL_TEST_MACRO(bRC == false,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSampleVariance()",
                          "invalid input data");

      unsigned int finalPosPlus1 = initialPos + numPos;
      T diff;
      T localSamValue = 0.;
      for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
        diff = m_seq[j] - unifiedMeanValue;
        localSamValue += diff*diff;
      }

      unsigned int unifiedNumPos = 0;
      int mpiRC = MPI_Allreduce((void *) &numPos, (void *) &unifiedNumPos, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSampleVariance()",
                          "failed MPI_Allreduce() for numPos");

      mpiRC = MPI_Allreduce((void *) &localSamValue, (void *) &unifiedSamValue, (int) 1, MPI_DOUBLE, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSampleVariance()",
                          "failed MPI_Allreduce() for samValue");

      unifiedSamValue /= (((T) unifiedNumPos) - 1.);
    }
    else {
      // Node not in the 'inter0' communicator
      this->subSampleVariance(initialPos,
                              numPos,
                              unifiedMeanValue);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedSampleVariance()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return unifiedSamValue;
}

template <class T>
T
uqScalarSequenceClass<T>::subPopulationVariance(
  unsigned int initialPos,
  unsigned int numPos,
  const T&     meanValue) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subPopulationVariance()",
                      "invalid input data");

  unsigned int finalPosPlus1 = initialPos + numPos;
  T diff;
  T popValue = 0.;
  for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
    diff = m_seq[j] - meanValue;
    popValue += diff*diff;
  }

  popValue /= (T) numPos;

  return popValue;
}

template <class T>
T
uqScalarSequenceClass<T>::unifiedPopulationVariance(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  unsigned int numPos,
  const T&     unifiedMeanValue) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subPopulationVariance(initialPos,
                                       numPos,
                                       unifiedMeanValue);
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  T unifiedPopValue = 0.;
  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      bool bRC = ((initialPos          <  this->subSequenceSize()) &&
                  (0                   <  numPos                 ) &&
                  ((initialPos+numPos) <= this->subSequenceSize()));
      UQ_FATAL_TEST_MACRO(bRC == false,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedPopulationVariance()",
                          "invalid input data");

      unsigned int finalPosPlus1 = initialPos + numPos;
      T diff;
      T localPopValue = 0.;
      for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
        diff = m_seq[j] - unifiedMeanValue;
        localPopValue += diff*diff;
      }

      unsigned int unifiedNumPos = 0;
      int mpiRC = MPI_Allreduce((void *) &numPos, (void *) &unifiedNumPos, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedPopulationVariance()",
                          "failed MPI_Allreduce() for numPos");

      mpiRC = MPI_Allreduce((void *) &localPopValue, (void *) &unifiedPopValue, (int) 1, MPI_DOUBLE, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedPopulationVariance()",
                          "failed MPI_Allreduce() for popValue");

      unifiedPopValue /= ((T) unifiedNumPos);
    }
    else {
      // Node not in the 'inter0' communicator
      this->subPopulationVariance(initialPos,
                                  numPos,
                                  unifiedMeanValue);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedPopulationVariance()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return unifiedPopValue;
}

template <class T>
T
uqScalarSequenceClass<T>::autoCovariance(
  unsigned int initialPos,
  unsigned int numPos,
  const T&     meanValue,
  unsigned int lag) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()) &&
              (lag                 <  numPos                 )); // lag should not be too large
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::autoCovariance()",
                      "invalid input data");

  unsigned int loopSize      = numPos - lag;
  unsigned int finalPosPlus1 = initialPos + loopSize;
  T diff1;
  T diff2;
  T covValue = 0.;
  for (unsigned int j = initialPos; j < finalPosPlus1; ++j) {
    diff1 = m_seq[j    ] - meanValue;
    diff2 = m_seq[j+lag] - meanValue;
    covValue += diff1*diff2;
  }

  covValue /= (T) loopSize;

  return covValue;
}

template <class T>
T
uqScalarSequenceClass<T>::autoCorrViaDef(
  unsigned int initialPos,
  unsigned int numPos,
  unsigned int lag) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()) &&
              (0                   <  numPos                 ) &&
              ((initialPos+numPos) <= this->subSequenceSize()) &&
              (lag                 <  numPos                 )); // lag should not be too large
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::autoCorrViaDef()",
                      "invalid input data");

  T meanValue = this->subMean(initialPos,
                              numPos);

  T covValueZero = this->autoCovariance(initialPos,
                                        numPos,
                                        meanValue,
                                        0); // lag

  T corrValue = this->autoCovariance(initialPos,
                                     numPos,
                                     meanValue,
                                     lag);

  return corrValue/covValueZero;
}

template <class T>
void
uqScalarSequenceClass<T>::autoCorrViaFft(
  unsigned int    initialPos,
  unsigned int    numPos,
  unsigned int    maxLag,
  std::vector<T>& autoCorrs) const
{
  unsigned int fftSize = 0;
  {
    double tmp = log((double) maxLag)/log(2.);
    double fractionalPart = tmp - ((double) ((unsigned int) tmp));
    if (fractionalPart > 0.) tmp += (1. - fractionalPart);
    unsigned int fftSize1 = (unsigned int) std::pow(2.,tmp+1.); // Yes, tmp+1
    fftSize1 = fftSize1; // To remove warning

    tmp = log((double) numPos)/log(2.);
    fractionalPart = tmp - ((double) ((unsigned int) tmp));
    if (fractionalPart > 0.) tmp += (1. - fractionalPart);
    unsigned int fftSize2 = (unsigned int) std::pow(2.,tmp+1);

    fftSize = fftSize2;
  }

  std::vector<double> rawDataVec(numPos,0.);
  std::vector<std::complex<double> > resultData(0,std::complex<double>(0.,0.));
  uqFftClass<T> fftObj(m_env);

  // Forward FFT
  this->extractRawData(initialPos,
                       1, // spacing
                       numPos,
                       rawDataVec);
  T meanValue = this->subMean(initialPos,
                              numPos);
  for (unsigned int j = 0; j < numPos; ++j) {
    rawDataVec[j] -= meanValue; // IMPORTANT
  }

  rawDataVec.resize(fftSize,0.);

  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::autoCorrViaFft()"
  //                          << ": about to call fftObj.forward()"
  //                          << " with rawDataVec.size() = " << rawDataVec.size()
  //                          << ", fftSize = "            << fftSize
  //                          << ", resultData.size() = "  << resultData.size()
  //                          << std::endl;
  //}
  fftObj.forward(rawDataVec,fftSize,resultData);

  // Inverse FFT
  for (unsigned int j = 0; j < fftSize; ++j) {
    rawDataVec[j] = std::norm(resultData[j]);
  }
  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::autoCorrViaFft()"
  //                          << ": about to call fftObj.inverse()"
  //                          << " with rawDataVec.size() = " << rawDataVec.size()
  //                          << ", fftSize = "            << fftSize
  //                          << ", resultData.size() = "  << resultData.size()
  //                          << std::endl;
  //}
  fftObj.inverse(rawDataVec,fftSize,resultData);
  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::autoCorrViaFft()"
  //                          << ": returned succesfully from fftObj.inverse()"
  //                          << std::endl;
  //}

  // Prepare return data
  autoCorrs.resize(maxLag+1,0.); // Yes, +1
  for (unsigned int j = 0; j < autoCorrs.size(); ++j) {
    double ratio = ((double) j)/((double) (numPos-1));
    autoCorrs[j] = ( resultData[j].real()/resultData[0].real() )*(1.-ratio);
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::autoCorrViaFft(
  unsigned int initialPos,
  unsigned int numPos,
  unsigned int numSum,
  T&           autoCorrsSum) const
{
  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "Entering uqScalarSequenceClass<T>::autoCorrViaFft(), for sum"
  //                          << ": initialPos = " << initialPos
  //                          << ", numPos = "     << numPos
  //                          << std::endl;
  //}

  double tmp = log((double) numPos)/log(2.);
  double fractionalPart = tmp - ((double) ((unsigned int) tmp));
  if (fractionalPart > 0.) tmp += (1. - fractionalPart);
  unsigned int fftSize = (unsigned int) std::pow(2.,tmp+1);

  std::vector<double> rawDataVec(numPos,0.);
  std::vector<std::complex<double> > resultData(0,std::complex<double>(0.,0.));
  uqFftClass<T> fftObj(m_env);

  // Forward FFT
  this->extractRawData(initialPos,
                       1, // spacing
                       numPos,
                       rawDataVec);
  T meanValue = this->subMean(initialPos,
                              numPos);
  for (unsigned int j = 0; j < numPos; ++j) {
    rawDataVec[j] -= meanValue; // IMPORTANT
  }
  rawDataVec.resize(fftSize,0.);

  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::autoCorrViaFft(), for sum"
  //                          << ": about to call fftObj.forward()"
  //                          << " with rawDataVec.size() = " << rawDataVec.size()
  //                          << ", fftSize = "            << fftSize
  //                          << ", resultData.size() = "  << resultData.size()
  //                          << std::endl;
  //}
  fftObj.forward(rawDataVec,fftSize,resultData);

  // Inverse FFT
  for (unsigned int j = 0; j < fftSize; ++j) {
    rawDataVec[j] = std::norm(resultData[j]);
  }
  fftObj.inverse(rawDataVec,fftSize,resultData);

  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::autoCorrViaFft(), for sum"
  //                          << ": computed auto covariance for lag 0 = " << resultData[0].real()/((double) (numPos))
  //                          << ", computed resultData[0].imag() = "      << resultData[0].imag()
  //                          << std::endl;
  //}

  // Prepare return data
  autoCorrsSum = 0.;
  for (unsigned int j = 0; j < numSum; ++j) { // Yes, begin at lag '0'
    double ratio = ((double) j)/((double) (numPos-1));
    autoCorrsSum += ( resultData[j].real()/resultData[0].real() )*(1.-ratio);
  }

  return;
}

template <class T>
T
uqScalarSequenceClass<T>::bmm(
  unsigned int initialPos,
  unsigned int batchLength) const
{
  bool bRC = ((initialPos          <  this->subSequenceSize()            ) &&
              (batchLength         < (this->subSequenceSize()-initialPos)));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequences<T>::bmm()",
                      "invalid input data");

  unsigned int numberOfBatches = (this->subSequenceSize() - initialPos)/batchLength;
  uqScalarSequenceClass<T> batchMeans(m_env,numberOfBatches,"");

  for (unsigned int batchId = 0; batchId < numberOfBatches; batchId++) {
    batchMeans[batchId] = this->subMean(initialPos + batchId*batchLength,
                                        batchLength);
  }

  T meanOfBatchMeans = batchMeans.subMean(0,
                                          batchMeans.subSequenceSize());

  //T covLag0OfBatchMeans = batchMeans.autoCovariance(0,
  //                                                  batchMeans.subSequenceSize(),
  //                                                  meanOfBatchMeans,
  //                                                  0); // lag

  T bmmValue = batchMeans.subSampleVariance(0,
                                            batchMeans.subSequenceSize(),
                                            meanOfBatchMeans);

  bmmValue /= (T) batchMeans.subSequenceSize();           // CHECK
//bmmValue *= (T) (this->subSequenceSize() - initialPos); // CHECK

  return bmmValue;
}

template <class T>
void
uqScalarSequenceClass<T>::psd(
  unsigned int         initialPos,
  unsigned int         numBlocks,
  double               hopSizeRatio,
  std::vector<double>& psdResult) const
{
  bool bRC = ((initialPos         < this->subSequenceSize()                        ) &&
              (hopSizeRatio       != 0.                                            ) &&
              (numBlocks          <          (this->subSequenceSize() - initialPos)) &&
              (fabs(hopSizeRatio) < (double) (this->subSequenceSize() - initialPos)));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::psd()",
                      "invalid input data");

  unsigned int dataSize = this->subSequenceSize() - initialPos;

  T meanValue = this->subMean(initialPos,
                              dataSize);

  // Determine hopSize and blockSize
  unsigned int hopSize = 0;
  unsigned int blockSize = 0;
  if (hopSizeRatio <= -1.) {
    double overlapSize = -hopSizeRatio;
    double tmp = ((double) (dataSize + (numBlocks - 1)*overlapSize))/((double) numBlocks);
    blockSize = (unsigned int) tmp;
  }
  else if (hopSizeRatio < 0.) {
    double tmp = ((double) dataSize)/(( ((double) numBlocks) - 1. )*(-hopSizeRatio) + 1.);
    blockSize = (unsigned int) tmp;
    hopSize = (unsigned int) ( ((double) blockSize) * (-hopSizeRatio) );
  }
  else if (hopSizeRatio == 0.) {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::psd()",
                        "hopSizeRatio == 0");
  }
  else if (hopSizeRatio < 1.) {
    double tmp = ((double) dataSize)/(( ((double) numBlocks) - 1. )*hopSizeRatio + 1.);
    blockSize = (unsigned int) tmp;
    hopSize = (unsigned int) ( ((double) blockSize) * hopSizeRatio );
  }
  else {
    hopSize = (unsigned int) hopSizeRatio;
    blockSize = dataSize - (numBlocks - 1)*hopSize;
  }

  int numberOfDiscardedDataElements = dataSize - (numBlocks-1)*hopSize - blockSize;
  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "initialPos = "       << initialPos
  //                          << ", N = "              << dataSize
  //                          << ", #Blocks = "        << numBlocks
  //                          << ", R (hop size) = "   << hopSize
  //                          << ", B (block size) = " << blockSize
  //                          << ", overlap = "        << blockSize - hopSize
  //                          << ", [(#Blocks - 1) * R + B] = "       << (numBlocks-1)*hopSize + blockSize
  //                          << ", numberOfDiscardedDataElements = " << numberOfDiscardedDataElements
  //                          << std::endl;
  //}
  UQ_FATAL_TEST_MACRO(numberOfDiscardedDataElements < 0.,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::psd()",
                      "eventual extra space for last block should not be negative");

  double tmp = log((double) blockSize)/log(2.);
  double fractionalPart = tmp - ((double) ((unsigned int) tmp));
  if (fractionalPart > 0.) tmp += (1. - fractionalPart);
  unsigned int fftSize = (unsigned int) std::pow(2.,tmp);
  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "fractionalPart = " << fractionalPart
  //                          << ", B = "            << blockSize
  //                          << ", fftSize = "      << fftSize
  //                          << std::endl;
  //}

  double modificationScale = 0.;
  for (unsigned int j = 0; j < blockSize; ++j) {
    double tmpValue = uqMiscHammingWindow(blockSize-1,j);
    modificationScale += tmpValue*tmpValue;
  }
  modificationScale = 1./modificationScale;

  std::vector<double> blockData(blockSize,0.);
  uqFftClass<T> fftObj(m_env);
  std::vector<std::complex<double> > fftResult(0,std::complex<double>(0.,0.));

#if 0
  unsigned int halfFFTSize = fftSize/2;
  psdResult.clear();
  psdResult.resize(1+halfFFTSize,0.);
  double factor = 1./M_PI/((double) numBlocks); // /((double) blockSize);
#else
  psdResult.clear();
  psdResult.resize(fftSize,0.);
  double factor = 1./2./M_PI/((double) numBlocks); // /((double) blockSize);
#endif

  for (unsigned int blockId = 0; blockId < numBlocks; blockId++) {
    // Fill block using Hamming window
    unsigned int initialDataPos = initialPos + blockId*hopSize;
    for (unsigned int j = 0; j < blockSize; ++j) {
      unsigned int dataPos = initialDataPos + j;
      UQ_FATAL_TEST_MACRO(dataPos >= dataSize,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::psd()",
                          "too large position to be accessed in data");
      blockData[j] = uqMiscHammingWindow(blockSize-1,j) * ( m_seq[dataPos] - meanValue ); // IMPORTANT
    }

    fftObj.forward(blockData,fftSize,fftResult);

    //if (m_env.subDisplayFile()) {
    //  *m_env.subDisplayFile() << "blockData.size() = "   << blockData.size()
    //                          << ", fftSize = "          << fftSize
    //                          << ", fftResult.size() = " << fftResult.size()
    //                          << ", psdResult.size() = " << psdResult.size()
    //                          << std::endl;
    //}
    // Normalized spectral density: power per radians per sample
    for (unsigned int j = 0; j < psdResult.size(); ++j) {
      psdResult[j] += norm(fftResult[j])*modificationScale;
    }
  }

  for (unsigned int j = 0; j < psdResult.size(); ++j) {
    psdResult[j] *= factor;
  }

  return;
}

template <class T>
T
uqScalarSequenceClass<T>::geweke(
  unsigned int initialPos,
  double       ratioNa,
  double       ratioNb) const
{
  double doubleFullDataSize = (double) (this->subSequenceSize() - initialPos);
  uqScalarSequenceClass<T> tmpSeq(m_env,0,"");
  std::vector<double> psdResult(0,0.);

  unsigned int dataSizeA       = (unsigned int) (doubleFullDataSize * ratioNa);
  double       doubleDataSizeA = (double) dataSizeA;
  unsigned int initialPosA     = initialPos;
  this->extractScalarSeq(initialPosA,
                         1,
                         dataSizeA,
                         tmpSeq);
  double meanA = tmpSeq.subMean(0,
                                dataSizeA);
  tmpSeq.psd(0,
             (unsigned int) std::sqrt((double) dataSizeA),  // numBlocks
             .5, // hopSizeRatio
             psdResult);
  double psdA = psdResult[0];
  double varOfMeanA = 2.*M_PI*psdA/doubleDataSizeA;

  unsigned int dataSizeB       = (unsigned int) (doubleFullDataSize * ratioNb);
  double       doubleDataSizeB = (double) dataSizeB;
  unsigned int initialPosB     = this->subSequenceSize() - dataSizeB;
  this->extractScalarSeq(initialPosB,
                         1,
                         dataSizeB,
                         tmpSeq);
  double meanB = tmpSeq.subMean(0,
                                dataSizeB);
  tmpSeq.psd(0,
             (unsigned int) std::sqrt((double) dataSizeB),  // numBlocks
             .5, // hopSizeRatio
             psdResult);
  double psdB = psdResult[0];
  double varOfMeanB = 2.*M_PI*psdB/doubleDataSizeB;

  if (m_env.subDisplayFile()) {
    *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::geweke()"
                            << ", before computation of gewCoef"
                            << ":\n"
                            << ", dataSizeA = "       << dataSizeA
                            << ", numBlocksA = "      << (unsigned int) std::sqrt((double) dataSizeA)
                            << ", meanA = "           << meanA
                            << ", psdA = "            << psdA
                            << ", varOfMeanA = "      << varOfMeanA
                            << "\n"
                            << ", dataSizeB = "       << dataSizeB
                            << ", numBlocksB = "      << (unsigned int) std::sqrt((double) dataSizeB)
                            << ", meanB = "           << meanB
                            << ", psdB = "            << psdB
                            << ", varOfMeanB = "      << varOfMeanB
                            << std::endl;
  }
  double gewCoef = (meanA - meanB)/std::sqrt(varOfMeanA + varOfMeanB);

  return gewCoef;
}

template <class T>
T
uqScalarSequenceClass<T>::meanStacc(
  unsigned int initialPos) const
{
  UQ_FATAL_TEST_MACRO(true,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::meanStacc()",
                      "not implemented yet"); // ERNESTO

  double value = 0.;

  return value;
}

template <class T>
void
uqScalarSequenceClass<T>::subMinMax(
  unsigned int initialPos,
  unsigned int numPos,
  T&           minValue,
  T&           maxValue) const
{
  UQ_FATAL_TEST_MACRO((initialPos+numPos) > this->subSequenceSize(),
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subMinMax()",
                      "invalid input");

  seqScalarPositionConstIteratorTypedef pos1 = m_seq.begin();
  std::advance(pos1,initialPos);

  seqScalarPositionConstIteratorTypedef pos2 = m_seq.begin();
  std::advance(pos2,initialPos+numPos);

  if ((initialPos+numPos) == this->subSequenceSize()) {
    UQ_FATAL_TEST_MACRO(pos2 != m_seq.end(),
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::subMinMax()",
                        "invalid state");
  }

  seqScalarPositionConstIteratorTypedef pos;
  pos = std::min_element(pos1, pos2);
  minValue = *pos;
  pos = std::max_element(pos1, pos2);
  maxValue = *pos;

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::unifiedMinMax(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  unsigned int numPos,
  T&           unifiedMinValue,
  T&           unifiedMaxValue) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subMinMax(initialPos,
                           numPos,
                           unifiedMinValue,
                           unifiedMaxValue);
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      // Find local min and max
      T minValue;
      T maxValue;
      this->subMinMax(initialPos,
                      numPos,
                      minValue,
                      maxValue);

      // Get overall min
      std::vector<double> sendBuf(1,0.);
      for (unsigned int i = 0; i < sendBuf.size(); ++i) {
        sendBuf[i] = minValue;
      }
      int mpiRC = MPI_Allreduce((void *) &sendBuf[0], (void *) &unifiedMinValue, (int) sendBuf.size(), MPI_DOUBLE, MPI_MIN, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMinMax()",
                          "failed MPI_Allreduce() for min");

      // Get overall max
      for (unsigned int i = 0; i < sendBuf.size(); ++i) {
        sendBuf[i] = maxValue;
      }
      mpiRC = MPI_Allreduce((void *) &sendBuf[0], (void *) &unifiedMaxValue, (int) sendBuf.size(), MPI_DOUBLE, MPI_MAX, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedMinMax()",
                          "failed MPI_Allreduce() for max");

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedMinMax()"
                                << ": localMinValue = "   << minValue
                                << ", localMaxValue = "   << maxValue
                                << ", unifiedMinValue = " << unifiedMinValue
                                << ", unifiedMaxValue = " << unifiedMaxValue
                                << std::endl;
      }
    }
    else {
      // Node not in the 'inter0' communicator
      this->subMinMax(initialPos,
                      numPos,
                      unifiedMinValue,
                      unifiedMaxValue);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedMinMax()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subHistogram(
  unsigned int               initialPos,
  const T&                   minHorizontalValue,
  const T&                   maxHorizontalValue,
  std::vector<T>&            centers,
  std::vector<unsigned int>& bins) const
{
  UQ_FATAL_TEST_MACRO(centers.size() != bins.size(),
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subHistogram()",
                      "vectors 'centers' and 'bins' have different sizes");

  UQ_FATAL_TEST_MACRO(bins.size() < 3,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subHistogram()",
                      "number of 'bins' is too small: should be at least 3");

  for (unsigned int j = 0; j < bins.size(); ++j) {
    centers[j] = 0.;
    bins[j] = 0;
  }

  double horizontalDelta = (maxHorizontalValue - minHorizontalValue)/(((double) bins.size()) - 2.); // IMPORTANT: -2

  double minCenter = minHorizontalValue - horizontalDelta/2.;
  double maxCenter = maxHorizontalValue + horizontalDelta/2.;
  for (unsigned int j = 0; j < centers.size(); ++j) {
    double factor = ((double) j)/(((double) centers.size()) - 1.);
    centers[j] = (1. - factor) * minCenter + factor * maxCenter;
  }

  unsigned int dataSize = this->subSequenceSize();
  for (unsigned int j = 0; j < dataSize; ++j) {
    double value = m_seq[j];
    if (value < minHorizontalValue) {
      bins[0]++;
    }
    else if (value >= maxHorizontalValue) {
      bins[bins.size()-1]++;
    }
    else {
      unsigned int index = 1 + (unsigned int) ((value - minHorizontalValue)/horizontalDelta);
      bins[index]++;
    }
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::unifiedHistogram(
  bool                       useOnlyInter0Comm,
  unsigned int               initialPos,
  const T&                   unifiedMinHorizontalValue,
  const T&                   unifiedMaxHorizontalValue,
  std::vector<T>&            unifiedCenters,
  std::vector<unsigned int>& unifiedBins) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subHistogram(initialPos,
                              unifiedMinHorizontalValue,
                              unifiedMaxHorizontalValue,
                              unifiedCenters,
                              unifiedBins);
  }

  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      UQ_FATAL_TEST_MACRO(unifiedCenters.size() != unifiedBins.size(),
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedHistogram()",
                          "vectors 'unifiedCenters' and 'unifiedBins' have different sizes");

      UQ_FATAL_TEST_MACRO(unifiedBins.size() < 3,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedHistogram()",
                          "number of 'unifiedBins' is too small: should be at least 3");

      for (unsigned int j = 0; j < unifiedBins.size(); ++j) {
        unifiedCenters[j] = 0.;
        unifiedBins[j] = 0;
      }

      double unifiedHorizontalDelta = (unifiedMaxHorizontalValue - unifiedMinHorizontalValue)/(((double) unifiedBins.size()) - 2.); // IMPORTANT: -2

      double unifiedMinCenter = unifiedMinHorizontalValue - unifiedHorizontalDelta/2.;
      double unifiedMaxCenter = unifiedMaxHorizontalValue + unifiedHorizontalDelta/2.;
      for (unsigned int j = 0; j < unifiedCenters.size(); ++j) {
        double factor = ((double) j)/(((double) unifiedCenters.size()) - 1.);
        unifiedCenters[j] = (1. - factor) * unifiedMinCenter + factor * unifiedMaxCenter;
      }

      std::vector<unsigned int> localBins(unifiedBins.size(),0);
      unsigned int dataSize = this->subSequenceSize();
      for (unsigned int j = 0; j < dataSize; ++j) {
        double value = m_seq[j];
        if (value < unifiedMinHorizontalValue) {
          localBins[0]++;
        }
        else if (value >= unifiedMaxHorizontalValue) {
          localBins[localBins.size()-1]++;
        }
        else {
          unsigned int index = 1 + (unsigned int) ((value - unifiedMinHorizontalValue)/unifiedHorizontalDelta);
          localBins[index]++;
        }
      }

      int mpiRC = MPI_Allreduce((void *) &localBins[0], (void *) &unifiedBins[0], (int) localBins.size(), MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedHistogram()",
                          "failed MPI_Allreduce() for bins");

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
        for (unsigned int i = 0; i < unifiedCenters.size(); ++i) {
          *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedHistogram()"
                                  << ": i = " << i
                                  << ", unifiedMinHorizontalValue = " << unifiedMinHorizontalValue
                                  << ", unifiedMaxHorizontalValue = " << unifiedMaxHorizontalValue
                                  << ", unifiedCenters = "            << unifiedCenters[i]
                                  << ", unifiedBins = "               << unifiedBins[i]
                                  << std::endl;
        }
      }
    }
    else {
      // Node not in the 'inter0' communicator
      this->subHistogram(initialPos,
                         unifiedMinHorizontalValue,
                         unifiedMaxHorizontalValue,
                         unifiedCenters,
                         unifiedBins);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedHistogram()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subBasicHistogram(
  unsigned int                initialPos,
  const T&                    minHorizontalValue,
  const T&                    maxHorizontalValue,
  uqUniformOneDGridClass<T>*& gridValues,
  std::vector<unsigned int>&  bins) const
{
  UQ_FATAL_TEST_MACRO(bins.size() < 3,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subBasicHistogram()",
                      "number of 'bins' is too small: should be at least 3");

  for (unsigned int j = 0; j < bins.size(); ++j) {
    bins[j] = 0;
  }

  double horizontalDelta = (maxHorizontalValue - minHorizontalValue)/(((double) bins.size()) - 2.); // IMPORTANT: -2
  double minCenter = minHorizontalValue - horizontalDelta/2.;
  double maxCenter = maxHorizontalValue + horizontalDelta/2.;
  gridValues = new uqUniformOneDGridClass<T>(m_env,
                                             "",
                                             bins.size(),
	                                     minCenter,
	                                     maxCenter);

  unsigned int dataSize = this->subSequenceSize();
  for (unsigned int j = 0; j < dataSize; ++j) {
    double value = m_seq[j];
    if (value < minHorizontalValue) {
      bins[0] += value;
    }
    else if (value >= maxHorizontalValue) {
      bins[bins.size()-1] += value;
    }
    else {
      unsigned int index = 1 + (unsigned int) ((value - minHorizontalValue)/horizontalDelta);
      bins[index] += value;
    }
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subWeigthHistogram(
  unsigned int                initialPos,
  const T&                    minHorizontalValue,
  const T&                    maxHorizontalValue,
  uqUniformOneDGridClass<T>*& gridValues,
  std::vector<unsigned int>&  bins) const
{
  UQ_FATAL_TEST_MACRO(bins.size() < 3,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subWeigthHistogram()",
                      "number of 'bins' is too small: should be at least 3");

  for (unsigned int j = 0; j < bins.size(); ++j) {
    bins[j] = 0;
  }

  double horizontalDelta = (maxHorizontalValue - minHorizontalValue)/(((double) bins.size()) - 2.); // IMPORTANT: -2
  double minCenter = minHorizontalValue - horizontalDelta/2.;
  double maxCenter = maxHorizontalValue + horizontalDelta/2.;
  gridValues = new uqUniformOneDGridClass<T>(m_env,
                                             "",
                                             bins.size(),
	                                     minCenter,
	                                     maxCenter);

  unsigned int dataSize = this->subSequenceSize();
  for (unsigned int j = 0; j < dataSize; ++j) {
    double value = m_seq[j];
    if (value < minHorizontalValue) {
      bins[0] += value;
    }
    else if (value >= maxHorizontalValue) {
      bins[bins.size()-1] += value;
    }
    else {
      unsigned int index = 1 + (unsigned int) ((value - minHorizontalValue)/horizontalDelta);
      bins[index] += value;
    }
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subCdfStacc(
  unsigned int                    initialPos,
  std::vector<double>&            cdfStaccValues,
  std::vector<double>&            cdfStaccValuesUp,
  std::vector<double>&            cdfStaccValuesLow,
  const uqScalarSequenceClass<T>& sortedDataValues) const
{
  UQ_FATAL_TEST_MACRO(false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subCdfStacc()",
                      "not implemented yet"); // Joseph
  bool bRC = (initialPos                 <  this->subSequenceSize()  );
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<V>::subGaussianKDE()",
                      "invalid input data");

  unsigned int numPoints = subSequenceSize()-initialPos;
  double       auxNumPoints = numPoints;
  double       maxLamb = 0.;
  std::vector<double> ro      (numPoints,0.);
  std::vector<double> Isam_mat(numPoints,0.);

  for (unsigned int pointId = 0; pointId < numPoints; pointId++) {
    double p = ( ((double) pointId) + 1.0 )/auxNumPoints;
    double ro0 = p*(1.0-p);
    cdfStaccValues[pointId] = p;
       
    //std::cout << "x-data" << data[pointId]
    //          << std::endl;       
       
    for (unsigned int k = 0; k < numPoints; k++) {
      if (m_seq[k] <= sortedDataValues[pointId]) {
        Isam_mat[k] = 1;
      }
      else {
        Isam_mat[k] = 0;
      }
    }  

    for (unsigned int tau = 0; tau < (numPoints-1); tau++) {
      ro[tau] = 0.;
      for (unsigned int kk = 0; kk < numPoints-(tau+1); kk++) {
        ro[tau] += (Isam_mat[kk+tau+1]-p)*(Isam_mat[kk]-p);
      }
      ro[tau] *= 1.0/auxNumPoints;
    }
    double lamb = 0.;
    for (unsigned int tau = 0; tau < (numPoints-1); tau++) {
      double auxTau = tau;
      lamb += (1.-(auxTau+1.)/auxNumPoints)*ro[tau]/ro0;
      if (lamb > maxLamb) maxLamb = lamb;
    }
    lamb = 2.*maxLamb;

    //double ll=gsl_cdf_gaussian_Pinv(-0.05);
    cdfStaccValuesUp [pointId] = cdfStaccValues[pointId]+1.96*sqrt(ro0/auxNumPoints*(1.+lamb));
    cdfStaccValuesLow[pointId] = cdfStaccValues[pointId]-1.96*sqrt(ro0/auxNumPoints*(1.+lamb));
    if (cdfStaccValuesLow[pointId] < 0.) cdfStaccValuesLow[pointId] = 0.;
    if (cdfStaccValuesUp [pointId] > 1.) cdfStaccValuesUp [pointId] = 1.;
    //if (pointId==1 | pointId==100 | pointId==900) {
    //  std::cout<<lamb<<ll<<std::endl;
    //  std::cout<<lamb<<std::endl;
    //}
  }

#if 0
  unsigned int dataSize = this->subSequenceSize() - initialPos;
  unsigned int numEvals = evaluationPositions.size();

  for (unsigned int j = 0; j < numEvals; ++j) {
    double x = evaluationPositions[j];
    double value = 0.;
    for (unsigned int k = 0; k < dataSize; ++k) {
      double xk = m_seq[initialPos+k];
      value += 0.;//uqMiscGaussianDensity((x-xk)*scaleInv,0.,1.);
    }
    cdfStaccValues[j] = value/(double) dataSize;
  }
#endif

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subCdfStacc(
  unsigned int          initialPos,
  const std::vector<T>& evaluationPositions,
  std::vector<double>&  cdfStaccValues) const
{
  UQ_FATAL_TEST_MACRO(true,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subCdfStacc()",
                      "not implemented yet");

  bool bRC = ((initialPos                 <  this->subSequenceSize()   ) &&
              (0                          <  evaluationPositions.size()) &&
              (evaluationPositions.size() == cdfStaccValues.size()     ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<V>::subCdfStacc()",
                      "invalid input data");

  // For Joseph: 
  // Maybe sort first
  // For each of the evaluation positions:
  // --> 1) form temporary scalar seq that contains only 0 and 1
  // --> 2) call "temporary scalar seq"->meanStacc()

#if 0
  unsigned int dataSize = this->subSequenceSize() - initialPos;
  unsigned int numEvals = evaluationPositions.size();

  for (unsigned int j = 0; j < numEvals; ++j) {
    //double x = evaluationPositions[j];
    double value = 0.;
    for (unsigned int k = 0; k < dataSize; ++k) {
      //double xk = m_seq[initialPos+k];
      value += 0.;//uqMiscGaussianDensity((x-xk)*scaleInv,0.,1.);
    }
    cdfStaccValues[j] = value/(double) dataSize;
  }
#endif

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subSort(
  unsigned int              initialPos,
  uqScalarSequenceClass<T>& sortedSequence) const
{
  unsigned int numPos = this->subSequenceSize() - initialPos;
  sortedSequence.resizeSequence(numPos);
  this->extractScalarSeq(initialPos,
                         1,
                         numPos,
                         sortedSequence);
  sortedSequence.subSort();

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subSort()
{
  std::sort(m_seq.begin(), m_seq.end());
  return;
}

template <class T>
void
uqScalarSequenceClass<T>::unifiedSort(
  bool                      useOnlyInter0Comm,
  unsigned int              initialPos,
  uqScalarSequenceClass<T>& unifiedSortedSequence) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subSort(initialPos,unifiedSortedSequence);
  }

  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      //m_env.syncPrintDebugMsg("In uqScalarSequenceClass<T>::unifiedSort(), beginning logic",3,3000000,m_env.inter0Comm()); // Dangerous to barrier on inter0Comm ... // KAUST

      unsigned int localNumPos = this->subSequenceSize() - initialPos;

      std::vector<T> leafData(localNumPos,0.);
      this->extractRawData(0,
                           1,
                           localNumPos,
                           leafData);

      if (m_env.inter0Rank() == 0) {
        int minus1NumTreeLevels = 0;
        int power2NumTreeNodes  = 1;

        while (power2NumTreeNodes < m_env.inter0Comm().NumProc()) {
          power2NumTreeNodes += power2NumTreeNodes;
          minus1NumTreeLevels++;
        }

        if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
          *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedSort()"
                                  << ": sorting tree has " << m_env.inter0Comm().NumProc()
                                  << " nodes and "         << minus1NumTreeLevels+1
                                  << " levels"
                                  << std::endl;
        }

        this->parallelMerge(unifiedSortedSequence.rawData(),
                            leafData,
                            minus1NumTreeLevels);
      }
      else if (m_env.inter0Rank() > 0) { // KAUST
        unsigned int uintBuffer[1];
        MPI_Status   status;
        int mpiRC = MPI_Recv((void *) uintBuffer, 1, MPI_UNSIGNED, MPI_ANY_SOURCE, SCALAR_SEQUENCE_INIT_MPI_MSG, m_env.inter0Comm().Comm(), &status);
        UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                            m_env.worldRank(),
                            "uqScalarSequenceClass<T>::unifiedSort()",
                            "failed MPI_Recv() for init");

        unsigned int treeLevel = uintBuffer[0];
        this->parallelMerge(unifiedSortedSequence.rawData(),
                            leafData,
                            treeLevel);
      }

      //m_env.syncPrintDebugMsg("In uqScalarSequenceClass<T>::unifiedSort(), returned from parallelMerge()",3,3000000,m_env.inter0Comm()); // Dangerous to barrier on inter0Comm ... // KAUST

      // Broadcast
      unsigned int unifiedDataSize = unifiedSortedSequence.subSequenceSize();
      int mpiRC = MPI_Bcast((void *) &unifiedDataSize, (int) 1, MPI_UNSIGNED, 0, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSort()",
                          "failed MPI_Bcast() for unified data size");

      unsigned int sumOfNumPos = 0;
      mpiRC = MPI_Allreduce((void *) &localNumPos, (void *) &sumOfNumPos, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSort()",
                          "failed MPI_Allreduce() for data size");

      UQ_FATAL_TEST_MACRO(sumOfNumPos != unifiedDataSize,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSort()",
                          "incompatible unified sizes");

      unifiedSortedSequence.resizeSequence(unifiedDataSize);
      mpiRC = MPI_Bcast((void *) &unifiedSortedSequence.rawData()[0], (int) unifiedDataSize, MPI_DOUBLE, 0, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedSort()",
                          "failed MPI_Bcast() for unified data");

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::parallelMerge()"
                                << ": tree node "                                                                    << m_env.inter0Rank()
                                << ", unifiedSortedSequence[0] = "                                                   << unifiedSortedSequence[0]
                                << ", unifiedSortedSequence[" << unifiedSortedSequence.subSequenceSize()-1 << "] = " << unifiedSortedSequence[unifiedSortedSequence.subSequenceSize()-1]
                                << std::endl;
      }

      //m_env.syncPrintDebugMsg("In uqScalarSequenceClass<T>::unifiedSort(), ending logic",3,3000000,m_env.inter0Comm()); // Dangerous to barrier on inter0Comm ... // KAUST
    }
    else {
      // Node not in the 'inter0' communicator
      this->subSort(initialPos,unifiedSortedSequence);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedSort()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return;
}

// Acknowledgement: the tree idea in this routine was taken from
// 'http://penguin.ewu.edu/~trolfe/ParallelMerge/ParallelMerge.html', as of March 08, 2009
template <class T>
void
uqScalarSequenceClass<T>::parallelMerge(
  std::vector<T>&       sortedBuffer,
  const std::vector<T>& leafData,
  unsigned int          currentTreeLevel) const
{
  int parentNode = m_env.inter0Rank() & ~(1 << currentTreeLevel);

  if (m_env.inter0Rank() >= 0) { // KAUST
  if (currentTreeLevel == 0) {
    // Leaf node: sort own local data.
    unsigned int leafDataSize = leafData.size();
    sortedBuffer.resize(leafDataSize,0.);
    for (unsigned int i = 0; i < leafDataSize; ++i) {
      sortedBuffer[i] = leafData[i];
    }
    std::sort(sortedBuffer.begin(), sortedBuffer.end());
    if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
      *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::parallelMerge()"
                              << ": tree node "                                            << m_env.inter0Rank()
                              << ", leaf sortedBuffer[0] = "                               << sortedBuffer[0]
                              << ", leaf sortedBuffer[" << sortedBuffer.size()-1 << "] = " << sortedBuffer[sortedBuffer.size()-1]
                              << std::endl;
    }
  }
  else {
    int nextTreeLevel  = currentTreeLevel - 1;
    int rightChildNode = m_env.inter0Rank() | (1 << nextTreeLevel);

    if (rightChildNode >= m_env.inter0Comm().NumProc()) { // No right child. Move down one level.
      this->parallelMerge(sortedBuffer,
                          leafData,
                          nextTreeLevel);
    }
    else {
      unsigned int uintBuffer[1];
      uintBuffer[0] = nextTreeLevel;
      int mpiRC = MPI_Send((void *) uintBuffer, 1, MPI_UNSIGNED, rightChildNode, SCALAR_SEQUENCE_INIT_MPI_MSG, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::parallelMerge()",
                          "failed MPI_Send() for init");

      this->parallelMerge(sortedBuffer,
                          leafData,
                          nextTreeLevel);

      // Prepare variable 'leftSortedBuffer': just copy own current sorted data.
      unsigned int leftSize = sortedBuffer.size();
      std::vector<T> leftSortedBuffer(leftSize,0.);
      for (unsigned int i = 0; i < leftSize; ++i) {
        leftSortedBuffer[i] = sortedBuffer[i];
      }

      // Prepare variable 'rightSortedBuffer': receive data from right child node.
      MPI_Status   status;
      mpiRC = MPI_Recv((void *) uintBuffer, 1, MPI_UNSIGNED, rightChildNode, SCALAR_SEQUENCE_SIZE_MPI_MSG, m_env.inter0Comm().Comm(), &status);
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::parallelMerge()",
                          "failed MPI_Recv() for size");

      unsigned int rightSize = uintBuffer[0];
      std::vector<T> rightSortedBuffer(rightSize,0.);
      mpiRC = MPI_Recv((void *) &rightSortedBuffer[0], (int) rightSize, MPI_DOUBLE, rightChildNode, SCALAR_SEQUENCE_DATA_MPI_MSG, m_env.inter0Comm().Comm(), &status);
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::parallelMerge()",
                          "failed MPI_Recv() for data");

      // Merge the two results into 'sortedBuffer'.
      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::parallelMerge()"
                                << ": tree node "        << m_env.inter0Rank()
                                << " is combining "      << leftSortedBuffer.size()
                                << " left doubles with " << rightSortedBuffer.size()
                                << " right doubles"
                                << std::endl;
      }

      sortedBuffer.clear();
      sortedBuffer.resize(leftSortedBuffer.size()+rightSortedBuffer.size(),0.);
      unsigned int i = 0;
      unsigned int j = 0;
      unsigned int k = 0;
      while ((i < leftSize ) &&
             (j < rightSize)) {
        if (leftSortedBuffer[i] > rightSortedBuffer[j]) sortedBuffer[k++] = rightSortedBuffer[j++];
        else                                            sortedBuffer[k++] = leftSortedBuffer [i++];
      }
      while (i < leftSize ) sortedBuffer[k++] = leftSortedBuffer [i++];
      while (j < rightSize) sortedBuffer[k++] = rightSortedBuffer[j++];
      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::parallelMerge()"
                                << ": tree node "                                              << m_env.inter0Rank()
                                << ", merged sortedBuffer[0] = "                               << sortedBuffer[0]
                                << ", merged sortedBuffer[" << sortedBuffer.size()-1 << "] = " << sortedBuffer[sortedBuffer.size()-1]
                                << std::endl;
      }
    }
  }

  if (parentNode != m_env.inter0Rank()) {
    // Transmit data to parent node.
    unsigned int uintBuffer[1];
    uintBuffer[0] = sortedBuffer.size();
    int mpiRC = MPI_Send((void *) uintBuffer, 1, MPI_UNSIGNED, parentNode, SCALAR_SEQUENCE_SIZE_MPI_MSG, m_env.inter0Comm().Comm());
    UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::parallelMerge()",
                        "failed MPI_Send() for size");

    if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
      *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::parallelMerge()"
                              << ": tree node "                                          << m_env.inter0Rank()
                              << " is sending "                                          << sortedBuffer.size()
                              << " doubles to tree node "                                << parentNode 
                              << ", with sortedBuffer[0] = "                             << sortedBuffer[0]
                              << " and sortedBuffer[" << sortedBuffer.size()-1 << "] = " << sortedBuffer[sortedBuffer.size()-1]
                              << std::endl;
    }

    mpiRC = MPI_Send((void *) &sortedBuffer[0], (int) sortedBuffer.size(), MPI_DOUBLE, parentNode, SCALAR_SEQUENCE_DATA_MPI_MSG, m_env.inter0Comm().Comm());
    UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::parallelMerge()",
                        "failed MPI_Send() for data");
  }
  } // KAUST

  return;
}

template <class T>
T
uqScalarSequenceClass<T>::subInterQuantileRange(unsigned int initialPos) const
{
  UQ_FATAL_TEST_MACRO(initialPos >= this->subSequenceSize(),
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subInterQuantileRange()",
                      "'initialPos' is too big");

  uqScalarSequenceClass sortedSequence(m_env,0,"");
  this->subSort(initialPos,
                sortedSequence);

  // The test above guarantees that 'dataSize >= 1'
  unsigned int dataSize = this->subSequenceSize() - initialPos;

  UQ_FATAL_TEST_MACRO(dataSize != sortedSequence.subSequenceSize(),
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subInterQuantileRange()",
                      "inconsistent size variables");

  bool everythingOk = true;

  // pos1 = (dataSize+1)/4 - 1
  // pos1 >= 0            <==> dataSize   >= 3
  // pos1 <  (dataSize-1) <==> 3*dataSize >  1 
  unsigned int pos1 = (unsigned int) ( (((double) dataSize) + 1.)*1./4. - 1. );
  if (pos1 > (dataSize-1)) {
    pos1 = 0;
    everythingOk = false;
  }
  unsigned int pos1inc = pos1+1;
  if (pos1inc > (dataSize-1)) {
    pos1inc = dataSize-1;
    everythingOk = false;
  }

  // pos3 = (dataSize+1)*3/4 - 1
  // pos3 >= 0            <==> dataSize >= 1/3
  // pos3 <  (dataSize-1) <==> dataSize >  3 
  unsigned int pos3 = (unsigned int) ( (((double) dataSize) + 1.)*3./4. - 1. );
  if (pos3 > (dataSize-1)) {
    pos3 = 0;
    everythingOk = false;
  }
  unsigned int pos3inc = pos3+1;
  if (pos3inc > (dataSize-1)) {
    pos3inc = dataSize-1;
    everythingOk = false;
  }

  double fraction1 = (((double) dataSize) + 1.)*1./4. - 1. - ((double) pos1);
  if (fraction1 < 0.) {
    fraction1 = 0.;
    everythingOk = false;
  }
  double fraction3 = (((double) dataSize) + 1.)*3./4. - 1. - ((double) pos3);
  if (fraction3 < 0.) {
    fraction3 = 0.;
    everythingOk = false;
  }

  if (everythingOk == false) {
    std::cerr << "In uqScalarSequenceClass<T>::subInterQuantileRange()"
              << ", worldRank = " << m_env.worldRank()
              << ": at least one adjustment was necessary"
              << std::endl;
  }

  //if (m_env.subDisplayFile()) {
  //  *m_env.subDisplayFile() << "In uqScalarSequenceClass::subInterQuantileRange()"
  //                          << ", initialPos = "               << initialPos
  //                          << ", this->subSequenceSize() = "  << this->subSequenceSize()
  //                          << ", dataSize = "                 << dataSize
  //                          << ", sortedSequence.size() = "    << sortedSequence.size()
  //                          << ", pos1 = "                     << pos1
  //                          << ", pos3 = "                     << pos3
  //                          << std::endl;
  //}

  T value1 = (1.-fraction1) * sortedSequence[pos1] + fraction1 * sortedSequence[pos1inc];
  T value3 = (1.-fraction3) * sortedSequence[pos3] + fraction3 * sortedSequence[pos3inc];
  T iqrValue = value3 - value1;

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
    *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::subInterQuantileRange()"
                            << ": iqrValue = " << iqrValue
                            << ", dataSize = " << dataSize
                            << ", pos1 = "     << pos1
                            << ", pos3 = "     << pos3
                            << ", value1 = "   << value1
                            << ", value3 = "   << value3
                            << std::endl;

    // Save data only once into a separate file
    //std::ofstream* ofsvar = new std::ofstream(("sort_sub"+m_env.subIdString()+".m").c_str(), std::ofstream::out | std::ofstream::in | std::ofstream::ate);
    //if ((ofsvar            == NULL ) ||
    //    (ofsvar->is_open() == false)) {
    //  delete ofsvar;
    //  ofsvar = new std::ofstream(("sort_sub"+m_env.subIdString()+".m").c_str(), std::ofstream::out | std::ofstream::trunc);

    //  *ofsvar << "var_sort_sub" << m_env.subIdString() << " = zeros(" << 1
    //          << ","                                                  << dataSize
    //          << ");"
    //          << std::endl;
    //  for (unsigned int j = 0; j < dataSize; ++j) {
    //    *ofsvar << "var_sort_sub" << m_env.subIdString() << "(" << 1
    //            << ","                                          << j+1
    //            << ") = "                                       << sortedSequence[j]
    //            << ";"
    //            << std::endl;
    //  }
    //}
    //delete ofsvar;
  }


  return iqrValue;
}

template <class T>
T
uqScalarSequenceClass<T>::unifiedInterQuantileRange(
  bool         useOnlyInter0Comm,
  unsigned int initialPos) const
{
  T unifiedIqrValue = 0.;

  if (m_env.numSubEnvironments() == 1) {
    return this->subInterQuantileRange(initialPos);
  }

  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      //m_env.syncPrintDebugMsg("In uqScalarSequenceClass<T>::unifiedInterQuantileRange(), beginning logic",3,3000000,m_env.inter0Comm()); // Dangerous to barrier on inter0Comm ... // KAUST

      uqScalarSequenceClass unifiedSortedSequence(m_env,0,"");
      this->unifiedSort(useOnlyInter0Comm,
                        initialPos,
                        unifiedSortedSequence);
      unsigned int unifiedDataSize = unifiedSortedSequence.subSequenceSize();
    
      unsigned int localDataSize = this->subSequenceSize() - initialPos;
      unsigned int sumOfLocalSizes = 0;
      int mpiRC = MPI_Allreduce((void *) &localDataSize, (void *) &sumOfLocalSizes, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedInterQuantileRange()",
                          "failed MPI_Allreduce() for data size");

      UQ_FATAL_TEST_MACRO(sumOfLocalSizes != unifiedDataSize,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedInterQuantileRange()",
                          "incompatible unified sizes");

      unsigned int pos1 = (unsigned int) ( (((double) unifiedDataSize) + 1.)*1./4. - 1. );
      unsigned int pos3 = (unsigned int) ( (((double) unifiedDataSize) + 1.)*3./4. - 1. );

      double fraction1 = (((double) unifiedDataSize) + 1.)*1./4. - 1. - ((double) pos1);
      double fraction3 = (((double) unifiedDataSize) + 1.)*3./4. - 1. - ((double) pos3);

      T value1 = (1.-fraction1) * unifiedSortedSequence[pos1] + fraction1 * unifiedSortedSequence[pos1+1];
      T value3 = (1.-fraction3) * unifiedSortedSequence[pos3] + fraction3 * unifiedSortedSequence[pos3+1];
      unifiedIqrValue = value3 - value1;

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedInterQuantileRange()"
                                << ": unifiedIqrValue = " << unifiedIqrValue
                                << ", localDataSize = "   << localDataSize
                                << ", unifiedDataSize = " << unifiedDataSize
                                << ", pos1 = "            << pos1
                                << ", pos3 = "            << pos3
                                << ", value1 = "          << value1
                                << ", value3 = "          << value3
                                << std::endl;

        // Save data only once into a separate file
	//std::ofstream* ofsvar = new std::ofstream(("unif_sort_sub"+m_env.subIdString()+".m").c_str(), std::ofstream::out | std::ofstream::in | std::ofstream::ate);
        //if ((ofsvar            == NULL ) ||
        //    (ofsvar->is_open() == false)) {
        //  delete ofsvar;
        //  ofsvar = new std::ofstream(("unif_sort_sub"+m_env.subIdString()+".m").c_str(), std::ofstream::out | std::ofstream::trunc);

        //  *ofsvar << "var_unif_sort_sub" << m_env.subIdString() << " = zeros(" << 1
        //          << ","                                                       << unifiedDataSize
        //          << ");"
        //          << std::endl;
        //  for (unsigned int j = 0; j < unifiedDataSize; ++j) {
        //    *ofsvar << "var_unif_sort_sub" << m_env.subIdString() << "(" << 1
        //            << ","                                               << j+1
        //            << ") = "                                            << unifiedSortedSequence[j]
        //            << ";"
        //            << std::endl;
        //  }
        //}
        //delete ofsvar;
      }

      //m_env.syncPrintDebugMsg("In uqScalarSequenceClass<T>::unifiedInterQuantileRange(), ending logic",3,3000000,m_env.inter0Comm()); // Dangerous to barrier on inter0Comm ... // KAUST
    }
    else {
      // Node not in the 'inter0' communicator
      unifiedIqrValue = this->subInterQuantileRange(initialPos);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedInterQuantileRange()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return unifiedIqrValue;
}

template <class T>
T
uqScalarSequenceClass<T>::subScaleForKde(
  unsigned int initialPos,
  const T&     iqrValue,
  unsigned int kdeDimension) const
{
  bool bRC = (initialPos <  this->subSequenceSize());
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<V>::subScaleForKde()",
                      "invalid input data");

  unsigned int dataSize = this->subSequenceSize() - initialPos;

  T meanValue = this->subMean(initialPos,
                              dataSize);

  T samValue = this->subSampleVariance(initialPos,
                                       dataSize,
                                       meanValue);

  T scaleValue;
  if (iqrValue <= 0.) {
    scaleValue = 1.06*std::sqrt(samValue)/std::pow(dataSize,1./(4. + ((double) kdeDimension)));
   }
  else {
    scaleValue = 1.06*std::min(std::sqrt(samValue),iqrValue/1.34)/std::pow(dataSize,1./(4. + ((double) kdeDimension)));
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
    *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::subScaleForKde()"
                            << ": iqrValue = "   << iqrValue
                            << ", meanValue = "  << meanValue
                            << ", samValue = "   << samValue
                            << ", dataSize = "   << dataSize
                            << ", scaleValue = " << scaleValue
                            << std::endl;
  }

  return scaleValue;
}

template <class T>
T
uqScalarSequenceClass<T>::unifiedScaleForKde(
  bool         useOnlyInter0Comm,
  unsigned int initialPos,
  const T&     unifiedIqrValue,
  unsigned int kdeDimension) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subScaleForKde(initialPos,
                                unifiedIqrValue,
                                kdeDimension);
  }

  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  T unifiedScaleValue = 0.;
  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      bool bRC = (initialPos <  this->subSequenceSize());
      UQ_FATAL_TEST_MACRO(bRC == false,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<V>::unifiedScaleForKde()",
                          "invalid input data");

      unsigned int localDataSize = this->subSequenceSize() - initialPos;

      T unifiedMeanValue = this->unifiedMean(useOnlyInter0Comm,
                                             initialPos,
                                             localDataSize);

      T unifiedSamValue = this->unifiedSampleVariance(useOnlyInter0Comm,
                                                      initialPos,
                                                      localDataSize,
                                                      unifiedMeanValue);

      unsigned int unifiedDataSize = 0;
      int mpiRC = MPI_Allreduce((void *) &localDataSize, (void *) &unifiedDataSize, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedUniformlySampledCdf()",
                          "failed MPI_Allreduce() for data size");

      if (unifiedIqrValue <= 0.) {
        unifiedScaleValue = 1.06*std::sqrt(unifiedSamValue)/std::pow(unifiedDataSize,1./(4. + ((double) kdeDimension)));
      }
      else {
        unifiedScaleValue = 1.06*std::min(std::sqrt(unifiedSamValue),unifiedIqrValue/1.34)/std::pow(unifiedDataSize,1./(4. + ((double) kdeDimension)));
      }

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedScaleForKde()"
                                << ": unifiedIqrValue = "   << unifiedIqrValue
                                << ", unifiedMeanValue = "  << unifiedMeanValue
                                << ", unifiedSamValue = "   << unifiedSamValue
                                << ", unifiedDataSize = "   << unifiedDataSize
                                << ", unifiedScaleValue = " << unifiedScaleValue
                                << std::endl;
      }
    }
    else {
      // Node not in the 'inter0' communicator
      unifiedScaleValue = this->subScaleForKde(initialPos,
                                               unifiedIqrValue,
                                               kdeDimension);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedScaleForKde()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return unifiedScaleValue;
}

template <class T>
void
uqScalarSequenceClass<T>::subGaussian1dKde(
  unsigned int          initialPos,
  double                scaleValue,
  const std::vector<T>& evaluationPositions,
  std::vector<double>&  densityValues) const
{
  bool bRC = ((initialPos                 <  this->subSequenceSize()   ) &&
              (0                          <  evaluationPositions.size()) &&
              (evaluationPositions.size() == densityValues.size()      ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<V>::subGaussian1dKde()",
                      "invalid input data");

  unsigned int dataSize = this->subSequenceSize() - initialPos;
  unsigned int numEvals = evaluationPositions.size();

  double scaleInv = 1./scaleValue;
  for (unsigned int j = 0; j < numEvals; ++j) {
    double x = evaluationPositions[j];
    double value = 0.;
    for (unsigned int k = 0; k < dataSize; ++k) {
      double xk = m_seq[initialPos+k];
      value += uqMiscGaussianDensity((x-xk)*scaleInv,0.,1.);
    }
    densityValues[j] = scaleInv * (value/(double) dataSize);
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::unifiedGaussian1dKde(
  bool                  useOnlyInter0Comm,
  unsigned int          initialPos,
  double                unifiedScaleValue,
  const std::vector<T>& unifiedEvaluationPositions,
  std::vector<double>&  unifiedDensityValues) const
{
  if (m_env.numSubEnvironments() == 1) {
    return this->subGaussian1dKde(initialPos,
                                  unifiedScaleValue,
                                  unifiedEvaluationPositions,
                                  unifiedDensityValues);
  }

  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (m_env.inter0Rank() >= 0) {
      bool bRC = ((initialPos                        <  this->subSequenceSize()          ) &&
                  (0                                 <  unifiedEvaluationPositions.size()) &&
                  (unifiedEvaluationPositions.size() == unifiedDensityValues.size()      ));
      UQ_FATAL_TEST_MACRO(bRC == false,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<V>::unifiedGaussian1dKde()",
                          "invalid input data");

      unsigned int localDataSize = this->subSequenceSize() - initialPos;
      unsigned int unifiedDataSize = 0;
      int mpiRC = MPI_Allreduce((void *) &localDataSize, (void *) &unifiedDataSize, (int) 1, MPI_UNSIGNED, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedGaussian1dKde()",
                          "failed MPI_Allreduce() for data size");

      unsigned int numEvals = unifiedEvaluationPositions.size();

      std::vector<double> densityValues(numEvals,0.);
      double unifiedScaleInv = 1./unifiedScaleValue;
      for (unsigned int j = 0; j < numEvals; ++j) {
        double x = unifiedEvaluationPositions[j];
        double value = 0.;
        for (unsigned int k = 0; k < localDataSize; ++k) {
          double xk = m_seq[initialPos+k];
          value += uqMiscGaussianDensity((x-xk)*unifiedScaleInv,0.,1.);
        }
        densityValues[j] = value;
      }

      for (unsigned int j = 0; j < numEvals; ++j) {
        unifiedDensityValues[j] = 0.;
      }
      mpiRC = MPI_Allreduce((void *) &densityValues[0], (void *) &unifiedDensityValues[0], (int) numEvals, MPI_DOUBLE, MPI_SUM, m_env.inter0Comm().Comm());
      UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                          m_env.worldRank(),
                          "uqScalarSequenceClass<T>::unifiedGaussian1dKde()",
                          "failed MPI_Allreduce() for density values");

      for (unsigned int j = 0; j < numEvals; ++j) {
        unifiedDensityValues[j] *= unifiedScaleInv/((double) unifiedDataSize);
      }

      if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 0)) {
        *m_env.subDisplayFile() << "In uqScalarSequenceClass<T>::unifiedGaussian1dKde()"
                                << ": unifiedDensityValues[0] = "                                       << unifiedDensityValues[0]
                                << ", unifiedDensityValues[" << unifiedDensityValues.size()-1 << "] = " << unifiedDensityValues[unifiedDensityValues.size()-1]
                                << std::endl;
      }
    }
    else {
      // Node not in the 'inter0' communicator
      this->subGaussian1dKde(initialPos,
                             unifiedScaleValue,
                             unifiedEvaluationPositions,
                             unifiedDensityValues);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        m_env.worldRank(),
                        "uqScalarSequenceClass<T>::unifiedGaussian1dKde()",
                        "parallel vectors not supported yet");
  }

  //m_env.fullComm().Barrier();

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subWriteContents(
  const std::string&            fileName,
  const std::string&            fileType,
  const std::set<unsigned int>& allowedSubEnvIds) const
{
  UQ_FATAL_TEST_MACRO(m_env.subRank() < 0,
                      m_env.worldRank(),
                      "uqScalarSequenceClass<T>::subWriteContents()",
                      "unexpected subRank");

  uqFilePtrSetStruct filePtrSet;
  if (m_env.openOutputFile(fileName,
                           fileType,
                           allowedSubEnvIds,
                           false, // A 'true' causes problems when the user chooses (via options
                                  // in the input file) to use just one file for all outputs.
                           filePtrSet)) {
    this->subWriteContents(filePtrSet,fileType);
    this->closeFile(filePtrSet,fileType);
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::subWriteContents(
  std::ofstream&     ofs,
  const std::string& fileType) const // "m or hdf"
{
  ofs << m_name << "_sub" << m_env.subIdString() << " = zeros(" << this->subSequenceSize()
      << ","                                                    << 1
      << ");"
      << std::endl;
  ofs << m_name << "_sub" << m_env.subIdString() << " = [";
  unsigned int chainSize = this->subSequenceSize();
  for (unsigned int j = 0; j < chainSize; ++j) {
    ofs << m_seq[j]
        << std::endl;
  }
  ofs << "];\n";

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::unifiedWriteContents(
  const std::string& fileName,
  const std::string& fileType) const
{
  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ...
  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
    *m_env.subDisplayFile() << "Entering uqScalarSequenceClass<T>::unifiedWriteContents()"
                            << ": worldRank "       << m_env.worldRank()
                            << ", subEnvironment " << m_env.subId()
                            << ", subRank "        << m_env.subRank()
                            << ", inter0Rank "     << m_env.inter0Rank()
      //<< ", m_env.inter0Comm().NumProc() = " << m_env.inter0Comm().NumProc()
                            << ", fileName = "     << fileName
                            << ", fileType = "     << fileType
                            << std::endl;
  }

  // As of 14/Nov/2009, this routine does *not* require sub sequences to have equal size. Good.

  if (m_env.inter0Rank() >= 0) {
    for (unsigned int r = 0; r < (unsigned int) m_env.inter0Comm().NumProc(); ++r) {
      if (m_env.inter0Rank() == (int) r) {
        // My turn
        uqFilePtrSetStruct unifiedFilePtrSet;
        // bool writeOver = (r == 0);
        bool writeOver = false; // A 'true' causes problems when the user chooses (via options
                                // in the input file) to use just one file for all outputs.
        m_env.openUnifiedOutputFile(fileName,
                                    fileType, // "m or hdf"
                                    writeOver,
                                    unifiedFilePtrSet);

        if (r == 0) {
          *unifiedFilePtrSet.ofsVar << m_name << "_unified" << " = zeros(" << this->subSequenceSize()*m_env.inter0Comm().NumProc()
                         << ","                                 << 1
                         << ");"
                         << std::endl;
          *unifiedFilePtrSet.ofsVar << m_name << "_unified" << " = [";
        }

        unsigned int chainSize = this->subSequenceSize();
        for (unsigned int j = 0; j < chainSize; ++j) {
          *unifiedFilePtrSet.ofsVar << m_seq[j]
                         << std::endl;
        }

        m_env.closeFile(unifiedFilePtrSet,fileType);
      }
      m_env.inter0Comm().Barrier();
    }

    if (m_env.inter0Rank() == 0) {
      uqFilePtrSetStruct unifiedFilePtrSet;
      m_env.openUnifiedOutputFile(fileName,
                                  fileType,
                                  false, // Yes, 'writeOver = false' in order to close the array for matlab
                                  unifiedFilePtrSet);
      *unifiedFilePtrSet.ofsVar << "];\n";
      m_env.closeFile(unifiedFilePtrSet,fileType);
    }
  }

  if ((m_env.subDisplayFile()) && (m_env.displayVerbosity() >= 10)) {
    *m_env.subDisplayFile() << "Leaving uqScalarSequenceClass<T>::unifiedWriteContents()"
                            << ", fileName = " << fileName
                            << ", fileType = " << fileType
                            << std::endl;
  }
  //m_env.fullComm().Barrier(); // Dangerous to barrier on fullComm ...

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::extractScalarSeq(
  unsigned int              initialPos,
  unsigned int              spacing,
  unsigned int              numPos,
  uqScalarSequenceClass<T>& scalarSeq) const
{
  scalarSeq.resizeSequence(numPos);
  if (spacing == 1) {
    for (unsigned int j = 0; j < numPos; ++j) {
      //if ((initialPos+j*spacing) > m_seq.size()) {
      //  std::cerr << "In uqScalarSequenceClass<T>::extraScalarSeq()"
      //            << ": initialPos = " << initialPos
      //            << ", spacing = "    << spacing
      //            << ", numPos = "     << numPos
      //            << ", j = "          << j
      //            << ", position got too large"
      //            << std::endl;
      //}
      scalarSeq[j] = m_seq[initialPos+j        ];
    }
  }
  else {
    for (unsigned int j = 0; j < numPos; ++j) {
      //if ((initialPos+j*spacing) > m_seq.size()) {
      //  std::cerr << "In uqScalarSequenceClass<T>::extraScalarSeq()"
      //            << ": initialPos = " << initialPos
      //            << ", spacing = "    << spacing
      //            << ", numPos = "     << numPos
      //            << ", j = "          << j
      //            << ", position got too large"
      //            << std::endl;
      //}
      scalarSeq[j] = m_seq[initialPos+j*spacing];
    }
  }

  return;
}

template <class T>
void
uqScalarSequenceClass<T>::extractRawData(
  unsigned int         initialPos,
  unsigned int         spacing,
  unsigned int         numPos,
  std::vector<double>& rawDataVec) const
{
  rawDataVec.resize(numPos);
  if (spacing == 1) {
    for (unsigned int j = 0; j < numPos; ++j) {
      rawDataVec[j] = m_seq[initialPos+j        ];
    }
  }
  else {
    for (unsigned int j = 0; j < numPos; ++j) {
      rawDataVec[j] = m_seq[initialPos+j*spacing];
    }
  }

  return;
}

template <class T>
std::vector<T>&
uqScalarSequenceClass<T>::rawData()
{
  return m_seq;
}

template <class T>
void
uqComputeSubGaussian2dKde(const uqScalarSequenceClass<T>& scalarSeq1,
                          const uqScalarSequenceClass<T>& scalarSeq2,
                          unsigned int                    initialPos,
                          double                          scaleValue1,
                          double                          scaleValue2,
                          const std::vector<T>&           evaluationPositions1,
                          const std::vector<T>&           evaluationPositions2,
                          std::vector<double>&            densityValues)
{
  UQ_FATAL_TEST_MACRO(initialPos != 0,
                      scalarSeq1.env().worldRank(),
                      "uqComputeSubGaussian2dKde()",
                      "not implemented yet for initialPos != 0");

  double covValue  = 0.;
  double corrValue = 0.;
  uqComputeCovCorrBetweenScalarSequences(scalarSeq1,
                                         scalarSeq2,
                                         scalarSeq1.subSequenceSize(),
                                         covValue,
                                         corrValue);

  bool bRC = ((initialPos                   <  scalarSeq1.subSequenceSize()) &&
              (scalarSeq1.subSequenceSize() == scalarSeq2.subSequenceSize()) &&
              (0                            <  evaluationPositions1.size() ) &&
              (evaluationPositions1.size()  == evaluationPositions2.size() ) &&
              (evaluationPositions1.size()  == densityValues.size()        ));
  UQ_FATAL_TEST_MACRO(bRC == false,
                      scalarSeq1.env().worldRank(),
                      "uqComputeSubGaussian2dKde()",
                      "invalid input data");

  unsigned int dataSize = scalarSeq1.subSequenceSize() - initialPos;
  unsigned int numEvals = evaluationPositions1.size();

  double scale1Inv = 1./scaleValue1;
  double scale2Inv = 1./scaleValue2;
  //corrValue = 0.;
  double r = 1 - corrValue*corrValue;
  if (r <= 0.) { // prudencio 2010-07-23
    std::cerr << "In uqComputeSubGaussian2dKde()"
              << ": WARNING, r = " << r
              << std::endl;
  }
  //UQ_FATAL_TEST_MACRO(r < 0.,
  //                    scalarSeq1.env().worldRank(),
  //                    "uqComputeSubGaussian2dKde()",
  //                    "negative r");
  for (unsigned int j = 0; j < numEvals; ++j) {
    double x1 = evaluationPositions1[j];
    double x2 = evaluationPositions2[j];
    double value = 0.;
    for (unsigned int k = 0; k < dataSize; ++k) {
      double d1k = scale1Inv*(x1 - scalarSeq1[initialPos+k]);
      double d2k = scale2Inv*(x2 - scalarSeq2[initialPos+k]);
      value += exp(-.5*( d1k*d1k + 2*corrValue*d1k*d2k + d2k*d2k )/r);
    }
    densityValues[j] = scale1Inv * scale2Inv * (value/(double) dataSize) / 2. / M_PI / sqrt(r);
  }

  return;
}

template <class T>
void
uqComputeUnifiedGaussian2dKde(bool                            useOnlyInter0Comm,           // INPUT
                              const uqScalarSequenceClass<T>& scalarSeq1,                  // INPUT
                              const uqScalarSequenceClass<T>& scalarSeq2,                  // INPUT
                              unsigned int                    initialPos,                  // INPUT
                              double                          unifiedScaleValue1,          // INPUT
                              double                          unifiedScaleValue2,          // INPUT
                              const std::vector<T>&           unifiedEvaluationPositions1, // INPUT
                              const std::vector<T>&           unifiedEvaluationPositions2, // INPUT
                              std::vector<double>&            unifiedDensityValues)        // OUTPUT
{
  if (scalarSeq1.env().numSubEnvironments() == 1) {
    return uqComputeSubGaussian2dKde(scalarSeq1,
                                     scalarSeq2,
                                     initialPos,
                                     unifiedScaleValue1,
                                     unifiedScaleValue2,
                                     unifiedEvaluationPositions1,
                                     unifiedEvaluationPositions2,
                                     unifiedDensityValues);
  }

  // As of 14/Nov/2009, this routine needs to be checked if it requires sub sequences to have equal size. Good.

  if (useOnlyInter0Comm) {
    if (scalarSeq1.env().inter0Rank() >= 0) {
      UQ_FATAL_TEST_MACRO(true,
                          scalarSeq1.env().worldRank(),
                          "uqComputeUnifiedGaussian2dKde()",
                          "inter0 case not supported yet");
    }
    else {
      // Node not in the 'inter0' communicator
      uqComputeSubGaussian2dKde(scalarSeq1,
                                scalarSeq2,
                                initialPos,
                                unifiedScaleValue1,
                                unifiedScaleValue2,
                                unifiedEvaluationPositions1,
                                unifiedEvaluationPositions2,
                                unifiedDensityValues);
    }
  }
  else {
    UQ_FATAL_TEST_MACRO(true,
                        scalarSeq1.env().worldRank(),
                        "uqComputeUnifiedGaussian2dKde()",
                        "parallel vectors not supported yet");
  }

  //scalarSeq1.env().fullComm().Barrier();

  return;
}

template <class T>
void
uqComputeCovCorrBetweenScalarSequences(
  const uqScalarSequenceClass<T>& subPSeq,
  const uqScalarSequenceClass<T>& subQSeq,
        unsigned int              subNumSamples,
        T&                        covValue,
        T&                        corrValue)
{
  // Check input data consistency
  const uqBaseEnvironmentClass& env = subPSeq.env();

  UQ_FATAL_TEST_MACRO((subNumSamples > subPSeq.subSequenceSize()) || (subNumSamples > subQSeq.subSequenceSize()),
                      env.worldRank(),
                      "uqComputeCovCorrBetweenScalarSequences()",
                      "subNumSamples is too large");

  // For both P and Q vector sequences: fill them
  T tmpP = 0.;
  T tmpQ = 0.;

  // For both P and Q vector sequences: compute the unified mean
  T unifiedMeanP = subPSeq.unifiedMean(true,0,subNumSamples);
  T unifiedMeanQ = subQSeq.unifiedMean(true,0,subNumSamples);

  // Compute "sub" covariance matrix
  covValue = 0.;
  for (unsigned k = 0; k < subNumSamples; ++k) {
    // For both P and Q vector sequences: get the difference (wrt the unified mean) in them
    tmpP = subPSeq[k] - unifiedMeanP;
    tmpQ = subQSeq[k] - unifiedMeanQ;
    covValue += tmpP*tmpQ;
  }

  // For both P and Q vector sequences: compute the unified variance
  T unifiedSampleVarianceP = subPSeq.unifiedSampleVariance(true,
                                                           0,
                                                           subNumSamples,
                                                           unifiedMeanP);

  T unifiedSampleVarianceQ = subQSeq.unifiedSampleVariance(true,
                                                           0,
                                                           subNumSamples,
                                                           unifiedMeanQ);

  // Compute unified covariance
  if (env.inter0Rank() >= 0) {
    unsigned int unifiedNumSamples = 0;
    int mpiRC = MPI_Allreduce((void *) &subNumSamples, (void *) &unifiedNumSamples, (int) 1, MPI_UNSIGNED, MPI_SUM, env.inter0Comm().Comm());
    UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                        env.worldRank(),
                        "uqComputeCovCorrBetweenScalarSequences()",
                        "failed MPI_Allreduce() for subNumSamples");

    double aux = 0.;
    mpiRC = MPI_Allreduce((void *) &covValue, (void *) &aux, (int) 1, MPI_DOUBLE, MPI_SUM, env.inter0Comm().Comm());
    UQ_FATAL_TEST_MACRO(mpiRC != MPI_SUCCESS,
                        env.worldRank(),
                        "uqComputeCovCorrBetweenScalarSequences()",
                        "failed MPI_Allreduce() for a matrix position");
    covValue = aux/((double) (unifiedNumSamples-1)); // Yes, '-1' in order to compensate for the 'N-1' denominator factor in the calculations of sample variances above (whose square roots will be used below)

    corrValue = covValue/std::sqrt(unifiedSampleVarianceP)/std::sqrt(unifiedSampleVarianceQ);

    if ((corrValue < -1.) || (corrValue > 1.)) { // prudencio 2010-07-23
      std::cerr << "In uqComputeCovCorrBetweenScalarSequences()"
                << ": computed correlation is out of range, corrValue = " << corrValue
                << std::endl;
    }
    //UQ_FATAL_TEST_MACRO((corrValue < -1.) || (corrValue > 1.),
    //                    env.worldRank(),
    //                    "uqComputeCovCorrBetweenScalarSequences()",
    //                    "computed correlation is out of range");
  }
  else {
    // Node not in the 'inter0' communicator: do nothing extra
  }

  return;
}
#endif // __UQ_SCALAR_SEQUENCE_H__