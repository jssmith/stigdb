/* <stig/spa/honcho.h>

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

#include <stig/spa/any_honcho.h>
#include <stig/spa/flux_capacitor/flux_capacitor.h>
#include <stig/spa/service.h>
#include <stig/type/type_czar.h>

namespace Stig {

  namespace Spa {

    class THoncho
        : public TAnyHoncho {
      public:

      THoncho() {}

      virtual ~THoncho() {}

      virtual Spa::FluxCapacitor::TStore<Spa::FluxCapacitor::TSessionObj> &GetSessionObjStore() {
        assert(this);
        return SessionObjStore;
      }

      virtual Spa::FluxCapacitor::TStore<Spa::FluxCapacitor::TSharedPovObj> &GetSharedPovObjStore() {
        assert(this);
        return SharedPovObjStore;
      }

      virtual Spa::FluxCapacitor::TStore<Spa::FluxCapacitor::TPrivatePovObj> &GetPrivatePovObjStore() {
        assert(this);
        return PrivatePovObjStore;
      }

      virtual Spa::FluxCapacitor::TTetrisHandler &GetTetrisHandler() {
        assert(this);
        return TetrisHandler;
      }

      private:

      Type::TTypeCzar TypeCzar;

      Spa::FluxCapacitor::TStore<Spa::FluxCapacitor::TSessionObj> SessionObjStore;

      Spa::FluxCapacitor::TStore<Spa::FluxCapacitor::TSharedPovObj> SharedPovObjStore;

      Spa::FluxCapacitor::TStore<Spa::FluxCapacitor::TPrivatePovObj> PrivatePovObjStore;

      Spa::FluxCapacitor::TTetrisHandler TetrisHandler;

    };  // THoncho

  } // Spa

}  // Stig
