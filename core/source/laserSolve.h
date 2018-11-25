struct LaserSolver:Module
{
	tw::Float laserFreq;
	tw_polarization_type polarizationType;
	ComplexField a0,a1; // vector potential
	ComplexField chi; // defined by j = chi*a

	LaserPropagator *propagator;

	LaserSolver(const std::string& name,Grid* theGrid);
	virtual ~LaserSolver();
	virtual void ExchangeResources();
	virtual void Initialize();
	virtual void Reset();

	virtual void VerifyInput();
	virtual void ReadInputFileDirective(std::stringstream& inputString,const std::string& command);
	virtual void ReadData(std::ifstream& inFile);
	virtual void WriteData(std::ofstream& outFile);

	virtual void Update();

	virtual void BoxDiagnosticHeader(GridDataDescriptor*);
	virtual void PointDiagnosticHeader(std::ofstream& outFile);
	virtual void PointDiagnose(std::ofstream& outFile,const weights_3D& w);

	tw::vec3 GetIonizationKick(const tw::Float& a2,const tw::Float& q0,const tw::Float& m0);
};

struct QSSolver:LaserSolver
{
	QSSolver(const std::string& name,Grid* theGrid);
};

struct PGCSolver:LaserSolver
{
	Field F;

	PGCSolver(const std::string& name,Grid* theGrid);
	virtual void ExchangeResources();
	virtual void Initialize();

	virtual void MoveWindow();
	virtual void AntiMoveWindow();

	virtual void EnergyHeadings(std::ofstream& outFile);
	virtual void EnergyColumns(std::vector<tw::Float>& cols,std::vector<bool>& avg,const Region& theRgn);

	virtual void Update();
	virtual void ComputeFinalFields();

	virtual void BoxDiagnose(GridDataDescriptor*);
};
