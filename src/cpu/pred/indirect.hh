/*
 * Copyright (c) 2014 ARM Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CPU_PRED_INDIRECT_BASE_HH__
#define __CPU_PRED_INDIRECT_BASE_HH__

#include "arch/generic/pcstate.hh"
#include "config/the_isa.hh"
#include "cpu/inst_seq.hh"
#include "params/IndirectPredictor.hh"
#include "sim/sim_object.hh"

namespace gem5
{

namespace branch_prediction
{

class IndirectPredictor : public SimObject
{
  public:

    typedef IndirectPredictorParams Params;

    IndirectPredictor(const Params &params)
        : SimObject(params)
    {
    }

    virtual bool lookup(Addr br_addr, PCStateBase& br_target,
                        ThreadID tid) = 0;
    virtual void recordIndirect(Addr br_addr, Addr tgt_addr,
                                InstSeqNum seq_num, ThreadID tid) = 0;
    virtual void commit(InstSeqNum seq_num, ThreadID tid,
                        void * indirect_history) = 0;
    virtual void squash(InstSeqNum seq_num, ThreadID tid) = 0;
    virtual void recordTarget(InstSeqNum seq_num, void * indirect_history,
                              const PCStateBase& target, ThreadID tid) = 0;
    virtual void genIndirectInfo(ThreadID tid, void* & indirect_history) = 0;
    virtual void updateDirectionInfo(ThreadID tid, bool actually_taken) = 0;
    virtual void deleteIndirectInfo(ThreadID tid, void * indirect_history) = 0;
    virtual void changeDirectionPrediction(ThreadID tid,
                                           void * indirect_history,
                                           bool actually_taken) = 0;
    virtual unsigned getGhr(ThreadID tid) = 0;
};

} // namespace branch_prediction
} // namespace gem5

#endif // __CPU_PRED_INDIRECT_BASE_HH__
