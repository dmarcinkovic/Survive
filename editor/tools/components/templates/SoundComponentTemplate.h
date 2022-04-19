//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SOUNDCOMPONENTTEMPLATE_H
#define SURVIVE_SOUNDCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<SoundComponent>
	{
	private:
		OpenDialog m_OpenDialog{};
		AudioMaster m_AudioMaster{};

		bool m_Changed = true;
		bool m_Open = false;

	public:
		void drawComponent(SoundComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Sound", visible))
			{
				ImGui::Columns(2, nullptr, false);
				if (EditorUtil::drawColumnDragFloat("Pitch", "##Pitch", component.pitch, 0.0f, 5.0f, 0.1f))
				{
					component.audioSource.setPitch(component.pitch);
				}

				if (EditorUtil::drawColumnDragFloat("Gain", "##Gain", component.gain, 0.0f, 5.0f, 0.1f))
				{
					component.audioSource.setGain(component.gain);
				}

				EditorUtil::drawColumnInputBool("Play on loop", "##LoopSound", component.playOnLoop);
				ImGui::Separator();

				ImGui::Columns(2);

				loadSound(component.sound, component.soundFile);
				ImGui::Columns();
			}
		}

	private:
		void loadSound(ALint &sound, std::string &soundFile)
		{
			EditorUtil::showLoadedFile("Sound: %s", soundFile, "Load sound", m_Open);

			if (m_Open)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_Open);

				std::string selectedFilename = m_OpenDialog.getSelectedFilename();
				if (!m_Open && !selectedFilename.empty())
				{
					try
					{
						sound = m_AudioMaster.loadSound(selectedFilename.c_str());
						soundFile = selectedFilename;
						m_Changed = true;
					} catch (const std::exception &ignorable)
					{}
				}
			}
		}
	};
}

#endif //SURVIVE_SOUNDCOMPONENTTEMPLATE_H
