/*----------------------------------------------------------------------------
* spp2pgs - Generates BluRay PG Stream from Subtitles or AviSynth scripts
* by Giton Xu <adm@subelf.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*----------------------------------------------------------------------------*/

#pragma once

#include "SubPicProviderContextNet.h"

namespace Spp2PgsNet
{
	using namespace spp2pgs;
	
	public ref class SubPicProviderNet
	{
	public:
		SubPicProviderNet::!SubPicProviderNet()
		{
			if (nativeSpp != nullptr)
			{
				nativeSpp->Release();
				nativeSpp = nullptr;
			}
		}

		SubPicProviderNet::~SubPicProviderNet()
		{
			this->!SubPicProviderNet();
		
			this->sppCtx = nullptr;

			this->isDisposed = true;
		}

	internal:
		SubPicProviderNet(ISubPicProviderAlfa *spp, SubPicProviderContextNet ^sppCtx) :
			nativeSpp(spp), sppCtx(sppCtx) 
		{
			this->nativeSpp->AddRef();
		}

		property ISubPicProviderAlfa * NativeProvider
		{
			ISubPicProviderAlfa* get()
			{
				AssertNotDisposed();
				return nativeSpp;
			};
		};

	private:
		ISubPicProviderAlfa *nativeSpp;

		SubPicProviderContextNet ^sppCtx;

		bool isDisposed = false;

		void AssertNotDisposed()
		{
			String ^tObjName = "SubPicProviderNet";
			if (this->isDisposed) throw gcnew ObjectDisposedException(tObjName);
		}
	};

}