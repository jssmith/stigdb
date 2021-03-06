/* <stig/code_gen/take.cc>

   Implements <stig/code_gen/take.h>

   Copyright 2010-2014 Stig LLC

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#include <stig/code_gen/take.h>

#include <stig/type/seq.h>
#include <stig/type/unwrap.h>

using namespace Stig::CodeGen;

TTake::TPtr TTake::New(
    const L0::TPackage *package,
    const Type::TType &ret_type,
    const TInline::TPtr &seq,
    const TInline::TPtr &count) {
  return TPtr(new TTake(package, ret_type, seq, count));
}

void TTake::WriteExpr(TCppPrinter &out) const {
  assert(this);
  assert(&out);
  out
    << "TTakeGenerator<" << Type::UnwrapSequence(GetReturnType()) << ">::New("
    << Count << ", " << Seq << ')';
}

TTake::TTake(
    const L0::TPackage *package,
    const Type::TType &ret_type,
    const TInline::TPtr &seq,
    const TInline::TPtr &count)
    : TInline(package, ret_type),
      Count(count),
      Seq(seq) {}