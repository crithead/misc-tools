/** @class Gnome
 * A gnome is a short, forest dwelling humanoid.  Every gnome has a name,
 * and age, and a profession.  They may have other attribuites.
 */
class Gnome
{
public:
	/// Constructor.
	/// @param name The name of the Gnome.
	/// @param prof The Gnome's profession.
	Gnome(const std::string& name = "None",
          const std::string& prof = "None",
		  int age = 0);

	/// Copy constructor.
	Gnome(const Gnome&);

	/// Destructor.
	virtual ~Gnome();

	/** Get the gnome's age.
	 * @return The gnome's age in years.
	 */
	int Age(void) const;

	/** Get the gnome's name.
	 * @return The gnome's name.
	 */
	std::string Name(void) const;

	/** Get the gnome's profession.
	 * @return The gnome's profession.
	 */
    std::string Profession(void) const;

	/** Set the gnome's age in years.
	 * @param age The new age.
	 */
	void SetAge(int age);

	/** Set the gnome's name.
	 * @param name The gnome's new name.
	 */
	void SetName(const std::string &name);

	/** Set the gnome's profession.
	 * @param prof The gnome's new profession.
	 */
	void SetProfession(const std::string& prof);

	/** Assignemnt operator.
	 * @param that The other gnome.
	 */
	Gnome& operator=(const Gnome &that);
	//bool operator==(const Gnome &) const;
	//bool operator!=(const Gnome &) const;
	//friend std::ostream& operator<<(std::ostream&, const Gnome &);

private:
	/** The gnomes age in years. */
	int age;
	/** The gnome's name. */
	std::string name;
	/** The gnome's profession. */
	std::string profession;
};

bool operator==(const Gnome&, const Gnome&);
bool operator!=(const Gnome&, const Gnome&);
std::ostream& operator<<(std::ostream&, const Gnome &);

