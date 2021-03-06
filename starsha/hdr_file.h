/* <starsha/hdr_file.h>

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

#include <cassert>

#include <base/no_copy_semantics.h>
#include <starsha/corpus.h>

namespace Starsha {

  /* TODO */
  class TObjFile;

  /* TODO */
  class THdrFile
      : public TCorpus::TFile {
    NO_COPY_SEMANTICS(THdrFile);
    public:

    /* TODO */
    virtual const TKind *GetKind() const;

    /* TODO */
    TFile *TryGetBuildableImplFile() const;

    private:

    /* TODO */
    THdrFile(TCorpus *corpus, const std::string &rel_path)
        : TFile(corpus, rel_path) {
      Init();
    }

    /* TODO */
    THdrFile(TCorpus *corpus, const std::string &rel_path, time_t mod_time)
        : TFile(corpus, rel_path, mod_time) {
      Init();
    }

    /* TODO */
    virtual ~THdrFile();

    /* TODO */
    void Init() {
      assert(this);
      ImplFile = 0;
    }

    /* TODO */
    virtual void OnNew();

    /* TODO */
    TObjFile *ImplFile;

    /* TODO */
    static const TSpecificKind<THdrFile> Kind;

    /* TODO */
    friend class TSpecificKind<THdrFile>;

  };  // THdrFile

}  // Starsha
