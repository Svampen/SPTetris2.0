#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM

#include <SFML/Graphics.hpp>
#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	ParticleSystem(unsigned int count, float lifeTime);
	~ParticleSystem();
    

	void setEmitter(sf::Vector2f position);
	void update(sf::Time elapsed);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index);

	std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};
#endif