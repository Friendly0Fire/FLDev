#pragma once

using namespace System;

namespace Utilities {
	public ref class ProcessBarItem {
		public:
			ProcessBarItem(String^ text, int initTicks, bool prog);

			property int TimeLeft {
				int get() {
					return timeleft;
				}
			}
			property String^ Text {
				String^ get() {
					return txt;
				}
			}
			property bool Progress {
				bool get() {
					return progress;
				}
			}
			void Decrement();
			virtual bool Equals(Object^ obj) override;
			virtual String^ ToString() override;
		private:
			int timeleft;
			bool progress;
			String^ txt;
	};
}