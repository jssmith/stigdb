/* <stig/expr/free.h>

   TODO

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

#pragma once

#include <memory>

#include <base/no_copy_semantics.h>
#include <stig/expr/leaf.h>
#include <stig/shared_enum.h>

namespace Stig {

  namespace Expr {

    class TFree
        : public TLeaf {
      NO_COPY_SEMANTICS(TFree);
      public:

      typedef std::shared_ptr<TFree> TPtr;

      static TPtr New(const Type::TType &type, const TPosRange &pos_range, TAddrDir addr_dir);

      virtual void Accept(const TVisitor &visitor) const;

      virtual Type::TType GetType() const;

      TAddrDir GetDir() const {
        return AddrDir;
      }

      private:

      TFree(const Type::TType &type, const TPosRange &pos_range, TAddrDir addr_dir);

      const Type::TType Type;

      const TAddrDir AddrDir;

    };  // TFree

  }  // Expr

}  // Stig
