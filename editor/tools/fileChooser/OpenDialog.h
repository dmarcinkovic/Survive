//
// Created by david on 27. 12. 2021..
//

#ifndef SURVIVE_OPENDIALOG_H
#define SURVIVE_OPENDIALOG_H

#include "FileChooser.h"

namespace Survive
{
	class OpenDialog : public FileChooser
	{
	public:
		void open(float windowWidth, float windowHeight, bool *open) override;

	private:
		void drawOpenFilenameTextbox(bool *open);

		void openPressed(bool *open);

		void fillTableRow(const File &file, int index, bool *open) override;
	};

}

#endif //SURVIVE_OPENDIALOG_H
