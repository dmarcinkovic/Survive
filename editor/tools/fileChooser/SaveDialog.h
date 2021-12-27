//
// Created by david on 27. 12. 2021..
//

#ifndef SURVIVE_SAVEDIALOG_H
#define SURVIVE_SAVEDIALOG_H

#include "FileChooser.h"

namespace Survive
{
	class SaveDialog : public FileChooser
	{
	public:
		void open(float windowWidth, float windowHeight, bool *open) override;

	private:
		void drawSaveFilenameTextbox(bool *open);

		void savePressed(bool *open);
	};
}

#endif //SURVIVE_SAVEDIALOG_H
