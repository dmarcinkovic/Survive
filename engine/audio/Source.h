//
// Created by david on 13. 06. 2020..
//

#ifndef SURVIVE_SOURCE_H
#define SURVIVE_SOURCE_H

#include <glm/glm.hpp>
#include <AL/al.h>

namespace Survive
{
	class Source
	{
	private:
		ALuint m_Source{};

	public:
		explicit Source(float gain = 1.0f, float pitch = 1.0f);

		~Source();

		void play(ALint buffer) const;

		void stop() const;

		void pause() const;

		void continuePlaying() const;

		[[nodiscard]] bool isPlaying() const;

		void setOnLoop(bool loop) const;

		void setPosition(const glm::vec3 &pos) const;
	};
}

#endif //SURVIVE_SOURCE_H
