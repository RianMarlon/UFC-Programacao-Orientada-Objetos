#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "utils.hpp"

class HospitalException : public std::exception {
    std::string message;
  public:
    HospitalException(const std::string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class IPatient;

class IDoctor {
  public:
    virtual std::string getName() const = 0;
    virtual std::string getSpecialty() const  = 0;
    virtual std::map<std::string, std::shared_ptr<IPatient>> getPatients() const = 0;
    virtual void addPatient(std::shared_ptr<IPatient>) = 0;
    virtual void removePatient(std::string) = 0;
    virtual ~IDoctor() {};
};

class IPatient {
  public:
    virtual std::string getName() const = 0;
    virtual std::string getDiagnostic() const = 0;
    virtual std::map<std::string, std::shared_ptr<IDoctor>> getDoctors() const = 0;
    virtual void addDoctor(std::shared_ptr<IDoctor>) = 0;
    virtual void removeDoctor(std::string) = 0;
    virtual ~IPatient() {};
};

class Doctor : public IDoctor {
  private:
    std::string name;
    std::string specialty;
    std::map<std::string, std::shared_ptr<IPatient>> patients;

  public:
    Doctor(std::string name = "", std::string specialty = ""): IDoctor{} {
      this->name = name;
      this->specialty = specialty;
    }

    std::string getName() const override {
      return this->name;
    }

    std::string getSpecialty() const override {
      return this->specialty;
    }

    std::map<std::string, std::shared_ptr<IPatient>> getPatients() const override {
      return this->patients;
    }

    void addPatient(std::shared_ptr<IPatient> patient) override {
      auto it = this->patients.find(patient->getName());
      if (it != this->patients.end()) {
        throw HospitalException("medico ja esta associado a esse paciente");
      }

      this->patients.insert(std::make_pair(patient->getName(), patient));
    }

    void removePatient(std::string name) override {
      auto it = this->patients.find(name);
      if (it != this->patients.end()) {
        this->patients.erase(name);
      }
    }
};

std::ostream& operator <<(std::ostream& os, const IDoctor& doctor) {
  os << "Med: " << doctor.getName() << ":" << doctor.getSpecialty() << " ";
  os << "Pacs: [";
  auto patients = doctor.getPatients();
  auto it = patients.begin();
  while(it != patients.end()) {
    if (it != patients.begin()) {
      os << ", " << it->second->getName();
    } else {
      os << it->second->getName();
    } 

    it++;
  }
  os << "]";

  return os;
}

class Patient : public IPatient {
  private:
    std::string name;
    std::string diagnostic;
    std::map<std::string, std::shared_ptr<IDoctor>> doctors;

    std::shared_ptr<IDoctor> getDoctorBySpecialty(std::string specialty) {
      for (auto& [name, doctor] : this->doctors) {
        if (doctor->getSpecialty() == specialty) {
          return doctor;
        }
      }

      return nullptr;
    }
  public:
    Patient(std::string name = "", std::string diagnostic = ""): IPatient{} {
      this->name = name;
      this->diagnostic = diagnostic;
    }

    ~Patient() {}

    std::string getName() const override {
      return this->name;
    }

    std::string getDiagnostic() const override {
      return this->diagnostic;
    }

    std::map<std::string, std::shared_ptr<IDoctor>> getDoctors() const override {
      return this->doctors;
    }

    void addDoctor(std::shared_ptr<IDoctor> doctor) {
      auto it = this->doctors.find(doctor->getName());
      if (it != this->doctors.end()) {
        throw HospitalException("paciente ja esta associado a esse medico");
      }

      auto specialty = doctor->getSpecialty();
      auto doctorBySpecialty = this->getDoctorBySpecialty(specialty);
      if (doctorBySpecialty != nullptr) {
        throw HospitalException("ja existe outro medico da especialidade " + specialty);
      }

      this->doctors.insert(std::make_pair(doctor->getName(), doctor));
    }

    void removeDoctor(std::string name) override {
      auto it = this->doctors.find(name);
      if (it != this->doctors.end()) {
        this->doctors.erase(name);
      }
    }
};

std::ostream& operator <<(std::ostream& os, const IPatient& patient) {
  os << "Pac: " << patient.getName() << ":" << patient.getDiagnostic() << " ";
  os << "Meds: [";
  auto doctors = patient.getDoctors();
  auto it = doctors.begin();
  while(it != doctors.end()) {
    if (it != doctors.begin()) {
      os << ", " << it->second->getName();
    } else {
      os << it->second->getName();
    } 

    it++;
  }
  os << "]";
  
  return os;
}

class Hospital {
  private:
    std::map<std::string, std::shared_ptr<IDoctor>> doctors;
    std::map<std::string, std::shared_ptr<IPatient>> patients;

  public:
    Hospital() {}

    ~Hospital() {}

    void addDoctor(std::string name, std::string specialty) {
      auto it = this->doctors.find(name);
      if (it != this->doctors.end()) {
        throw HospitalException("medico ja cadastrado");
      }

      this->doctors.insert(std::make_pair(name, std::make_shared<Doctor>(name, specialty)));
    }

    void addPatient(std::string name, std::string diagnostic) {
      auto it = this->patients.find(name);
      if (it != this->patients.end()) {
        throw HospitalException("paciente ja cadastrado");
      }

      this->patients.insert(std::make_pair(name, std::make_shared<Patient>(name, diagnostic)));
    }

    void removeDoctor(std::string name) {
      auto it = this->doctors.find(name);
      if (it == this->doctors.end()) {
        throw HospitalException("doutor nao encontrado");
      }

      for (auto& [namePatient, patient] : this->patients) {
        patient->removeDoctor(name);
      }
      this->doctors.erase(name);
    }

    void removePatient(std::string name) {
      auto it = this->patients.find(name);
      if (it == this->patients.end()) {
        throw HospitalException("paciente nao encontrado");
      }

      for (auto& [nameDoctor, doctor] : this->doctors) {
        doctor->removePatient(name);
      }
      this->patients.erase(name);
    }

    void associate(std::string nameDoctor, std::string namePatient) {
      auto itPatient = this->patients.find(namePatient);
      if (itPatient == this->patients.end()) {
        throw HospitalException("paciente nao encontrado");
      }

      auto itDoctor = this->doctors.find(nameDoctor);
      if (itDoctor == this->doctors.end()) {
        throw HospitalException("doutor nao encontrado");
      }

      auto patient = this->patients[namePatient];
      auto doctor = this->doctors[nameDoctor];
      patient->addDoctor(doctor);
      doctor->addPatient(patient);
    }

    friend std::ostream& operator <<(std::ostream& os, const Hospital& hospital) {
      for (auto& [name, patient] : hospital.patients) {
        os << *patient << "\n";
      }

      for (auto& [name, doctor] : hospital.doctors) {
        os << *doctor << "\n";
      }
      
      return os;
    }
};

int main() {
  Hospital hospital;

  while(true) {
    std::string line;
    std::getline(std::cin, line);
    auto params = utils::split(line, ' ');
    auto cmd = params[0];
    
    try {
      if(cmd == "end") {
        break;
      } else if(cmd == "help") {
          std::cout << "show;\n"
            << "addDoctors _name:_specialty... ;\n"
            << "addPatients _name:_diagnostic...;\n"
            << "removeDoctor _name;\n"
            << "removePatient _name;\n"
            << "associate _doctor _patient...;\n"
            << "end;\n";
      } else if(cmd == "show") {
        std::cout << hospital << "\n";
      } else if(cmd == "addDoctors") {
        auto doctors = utils::slice(params, 1);

        for (auto doctor : doctors) {
          auto data = utils::split(doctor, '-');
          hospital.addDoctor(data[0], data[1]);
        }
      } else if(cmd == "addPatients") {
        auto patients = utils::slice(params, 1);

        for (auto patient : patients) {
          auto data = utils::split(patient, '-');
          hospital.addPatient(data[0], data[1]);
        }
      } else if(cmd == "removeDoctor") {
        hospital.removeDoctor(params[1]);
      } else if(cmd == "removePatient") {
        hospital.removePatient(params[1]);
      } else if(cmd == "associate") {
        auto doctor = params[1];
        auto patients = utils::slice(params, 2);

        for (auto patient : patients) {
          hospital.associate(doctor, patient);
        }
      } else {
        std::cout << "fail: comando invalido\n";
      }
    } catch (HospitalException& e) {
      std::cout << "fail: " << e.what() << "\n";
    }
  }
}
