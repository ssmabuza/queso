/* uq/libs/mcmc/inc/uqValidProblem.h
 *
 * Copyright (C) 2008 The PECOS Team, http://queso.ices.utexas.edu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __UQ_VALID_PROBLEM_H__
#define __UQ_VALID_PROBLEM_H__

#include <uqValidProblemStage.h>

#define UQ_VALID_PROBLEM_PREFIX_FOR_NO_STAGE_PREFIX "."

// _ODV = option default value
#define UQ_VALID_PROBLEM_NUM_STAGES_ODV     0
#define UQ_VALID_PROBLEM_STAGE_PREFIXES_ODV UQ_VALID_PROBLEM_PREFIX_FOR_NO_STAGE_PREFIX
#define UQ_VALID_PROBLEM_STAGE_ORDER_ODV    "0"

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
class uqValidProblemClass
{
public:
  uqValidProblemClass(const uqEnvironmentClass& env);
 ~uqValidProblemClass();

        void                                               instantiateStage (unsigned int                                           stageId,
                                                                             const uqProbDensity_BaseClass       <P_V,P_M>*         m2lPriorParamDensityObj,  // Set in substep x.1 in applications setting a validation problem stage
                                                                             const uqLikelihoodFunction_BaseClass<P_V,P_M,L_V,L_M>* m2lLikelihoodFunctionObj, // Set in substep x.2
                                                                             P_M*                                                   proposalCovMatrix,        // Set in substep x.3
                                                                             const uqProposalDensity_BaseClass   <P_V,P_M>*         proposalDensityObj,       // Set in substep x.3
                                                                             const uqProposalGenerator_BaseClass <P_V,P_M>*         proposalGeneratorObj,     // Set in substep x.3
                                                                             const uqProbDensity_BaseClass       <P_V,P_M>*         propagParamDensityObj,    // Set in substep x.4
                                                                             const uqSampleGenerator_BaseClass   <P_V,P_M>*         propagParamGeneratorObj,  // Set in substep x.4
                                                                             const uqQoIFunction_BaseClass       <P_V,P_M,Q_V,Q_M>* qoiFunctionObj);          // Set in substep x.5

  const uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>& stage            (unsigned int stageId) const;
        void                                               solve            ();

        void                                               print            (std::ostream& os) const;

private:
        void                                               defineMyOptions  (po::options_description& optionsDesc);
        void                                               getMyOptionValues(po::options_description& optionsDesc);

  const uqEnvironmentClass&                                       m_env;

  po::options_description*                                        m_optionsDesc;
  std::string                                                     m_option_help;
  std::string                                                     m_option_numStages;
  std::string                                                     m_option_stagePrefixes;
  std::string                                                     m_option_stageOrder;

  unsigned int                                                    m_numStages;
  std::vector<std::string>                                        m_stagePrefixes;
  std::vector<unsigned int>                                       m_stageOrder;
  std::vector<uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>*> m_stages;
};

template<class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
std::ostream& operator<<(std::ostream& os, const uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>& obj);

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::uqValidProblemClass(const uqEnvironmentClass& env)
  :
  m_env                 (env),
  m_optionsDesc         (new po::options_description("Validation Problem")),
  m_option_help         ("validProblem_help"         ),
  m_option_numStages    ("validProblem_numStages"    ),
  m_option_stagePrefixes("validProblem_stagePrefixes"),
  m_option_stageOrder   ("validProblem_stageOrder"   ),
  m_numStages           (UQ_VALID_PROBLEM_NUM_STAGES_ODV),
  m_stagePrefixes       (1,UQ_VALID_PROBLEM_STAGE_PREFIXES_ODV),
  m_stageOrder          (0),
  m_stages              (0)
{
  if (m_env.rank() == 0) std::cout << "Entering uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::constructor()"
                                   << std::endl;

  defineMyOptions                (*m_optionsDesc);
  m_env.scanInputFileForMyOptions(*m_optionsDesc);
  getMyOptionValues              (*m_optionsDesc);

  if (m_env.rank() == 0) std::cout << "In uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::constructor()"
                                   << ": after getting values of options, state of object is:"
                                   << "\n" << *this
                                   << std::endl;

  m_stages.resize(m_numStages,NULL);

  if (m_env.rank() == 0) std::cout << "Leaving uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::constructor()"
                                   << std::endl;
}

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::~uqValidProblemClass()
{
  for (unsigned int i = 0; i < m_stages.size(); ++i) {
    if (m_stages[i] != NULL) delete m_stages[i];
  }
  if (m_optionsDesc) delete m_optionsDesc;
}

template<class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
void
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::defineMyOptions(
  po::options_description& optionsDesc)
{
  optionsDesc.add_options()
    (m_option_help.c_str(),                                                                                         "produce help message for a validation problem")
    (m_option_numStages.c_str(),     po::value<unsigned int>()->default_value(UQ_VALID_PROBLEM_NUM_STAGES_ODV),     "number of stages"                             )
    (m_option_stagePrefixes.c_str(), po::value<std::string >()->default_value(UQ_VALID_PROBLEM_STAGE_PREFIXES_ODV), "list of prefix(es) for stage(s)"              )
    (m_option_stageOrder.c_str(),    po::value<std::string >()->default_value(UQ_VALID_PROBLEM_STAGE_ORDER_ODV),    "order of stages during solution process"      )
  ;

  return;
}

template<class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
void
  uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::getMyOptionValues(
  po::options_description& optionsDesc)
{
  if (m_env.allOptionsMap().count(m_option_help.c_str())) {
    std::cout << optionsDesc
              << std::endl;
  }

  if (m_env.allOptionsMap().count(m_option_numStages.c_str())) {
    m_numStages = m_env.allOptionsMap()[m_option_numStages.c_str()].as<unsigned int>();
  }

  if (m_env.allOptionsMap().count(m_option_stagePrefixes.c_str())) {
    m_stagePrefixes.clear();
    std::string inputString = m_env.allOptionsMap()[m_option_stagePrefixes.c_str()].as<std::string>();
    uqMiscReadWordsFromString(inputString,m_stagePrefixes);
    //std::cout << "In uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::getMyOptionValues()"
    //          << ": m_stagePrefixes[0] = " << m_stagePrefixes[0]
    //          << std::endl;
  }

  UQ_FATAL_TEST_MACRO(m_numStages != m_stagePrefixes.size(),
                      m_env.rank(),
                      "uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::getMyOptionsValues()",
                      "option 'numStages' is not equal to size of array of stage prefixes");

  if (m_env.allOptionsMap().count(m_option_stageOrder.c_str())) {
    m_stageOrder.clear();
    std::vector<double> tmpOrder(0,0.);
    std::string inputString = m_env.allOptionsMap()[m_option_stageOrder.c_str()].as<std::string>();
    uqMiscReadDoublesFromString(inputString,tmpOrder);

    if (tmpOrder.size() > 0) {
      m_stageOrder.resize(tmpOrder.size(),0);
      for (unsigned int i = 0; i < m_stageOrder.size(); ++i) {
        m_stageOrder[i] = (unsigned int) tmpOrder[i];
      }
    }
  }
  else {
    m_stageOrder.resize(m_numStages,0);
    for (unsigned int i = 0; i < m_stageOrder.size(); ++i) {
      m_stageOrder[i] = i;
    }
  }

  UQ_FATAL_TEST_MACRO(m_numStages != m_stageOrder.size(),
                      m_env.rank(),
                      "uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::getMyOptionsValues()",
                      "option 'numStages' is not equal to size of array of stage order");

  for (unsigned int i = 0; i < m_stageOrder.size(); ++i) {
    UQ_FATAL_TEST_MACRO(m_stageOrder[i] >= m_numStages,
                        m_env.rank(),
                        "uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::getMyOptionsValues()",
                        "a stage id on the array of stage order is too big");
  }

  return;
}

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
void
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::instantiateStage(
  unsigned int                                           stageId,
  const uqProbDensity_BaseClass       <P_V,P_M>*         m2lPriorParamDensityObj,  // Set in substep x.1
  const uqLikelihoodFunction_BaseClass<P_V,P_M,L_V,L_M>* m2lLikelihoodFunctionObj, // Set in substep x.2
  P_M*                                                   proposalCovMatrix,        // Set in substep x.3
  const uqProposalDensity_BaseClass   <P_V,P_M>*         proposalDensityObj,       // Set in substep x.3
  const uqProposalGenerator_BaseClass <P_V,P_M>*         proposalGeneratorObj,     // Set in substep x.3
  const uqProbDensity_BaseClass       <P_V,P_M>*         propagParamDensityObj,    // Set in substep x.4
  const uqSampleGenerator_BaseClass   <P_V,P_M>*         propagParamGeneratorObj,  // Set in substep x.4
  const uqQoIFunction_BaseClass       <P_V,P_M,Q_V,Q_M>* qoiFunctionObj)           // Set in substep x.5
{
  m_stages[stageId] = new uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>(m_env,
                                                                       m_stagePrefixes[stageId].c_str(),
                                                                       m2lPriorParamDensityObj,
                                                                       m2lLikelihoodFunctionObj,
                                                                       proposalCovMatrix,
                                                                       proposalDensityObj,
                                                                       proposalGeneratorObj,
                                                                       propagParamDensityObj,
                                                                       propagParamGeneratorObj,
                                                                       qoiFunctionObj);

  return;
}

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
const uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>&
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::stage(unsigned int stageId) const
{
  return *(m_stages[stageId]);
}

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
void
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::solve()
{
  for (unsigned int i = 0; i < m_numStages; ++i) {
    uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>* currentStage = m_stages[m_stageOrder[i]];
    if (currentStage->isCalibRequested()) {
      if (currentStage->calibInputStageId() < 0) {
        currentStage->calibrateParamDistribs();
      }
      else {
        unsigned int inputStageId = (unsigned int) currentStage->calibInputStageId();
        uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>* inputStage = m_stages[inputStageId];
        currentStage->calibrateParamDistribs(inputStage->posteriorParamDensityObj());
      }
    }
  }

  for (unsigned int i = 0; i < m_numStages; ++i) {
    uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>* currentStage = m_stages[m_stageOrder[i]];
    if (currentStage->isPropagRequested()) {
      if (currentStage->propagInputStageId() < 0) {
        currentStage->propagateParamDistribs();
      }
      else {
        unsigned int inputStageId = (unsigned int) currentStage->propagInputStageId();
        uqValidProblemStageClass<P_V,P_M,L_V,L_M,Q_V,Q_M>* inputStage = m_stages[inputStageId];
        currentStage->propagateParamDistribs(inputStage->posteriorParamGeneratorObj());
      }
    }
  }

  return;
}

template <class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
void
uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>::print(std::ostream& os) const
{
  os << "\n" << m_option_numStages     << " = " << m_numStages
     << "\n" << m_option_stagePrefixes << " = ";
  for (unsigned int i = 0; i < m_stagePrefixes.size(); ++i) {
    os << m_stagePrefixes[i] << " ";
  }
  os << "\n" << m_option_stageOrder << " = ";
  for (unsigned int i = 0; i < m_stageOrder.size(); ++i) {
    os << m_stageOrder[i] << " ";
  }
  os << std::endl;
}

template<class P_V,class P_M,class L_V,class L_M,class Q_V,class Q_M>
std::ostream& operator<<(std::ostream& os, const uqValidProblemClass<P_V,P_M,L_V,L_M,Q_V,Q_M>& obj)
{
  obj.print(os);

  return os;
}
#endif // __UQ_VALID_PROBLEM_H__
