Name:       libquillmetadata-qt5
Summary:    Qt based library for still image metadata manipulation
Version:    2.0.0
Release:    0
License:    LGPLv2 or GPLv3 or Qt Commercial or LGPLv2 with Nokia Qt LGPL Exception v1.1
URL:        https://github.com/sailfishos/quillmetadata
Source0:    %{name}-%{version}.tar.bz2
Requires:   qt5-plugin-imageformat-jpeg
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Test)
BuildRequires:  pkgconfig(libexif)
BuildRequires:  pkgconfig(exempi-2.0)
BuildRequires:  fdupes
BuildRequires:  libjpeg-devel
BuildRequires:  fdupes

%description
A Qt based library which can access and edit Exif, XMP and IPTC
metadata for still images (currently only JPEG format), offering
transparent reconciliation between different metadata representations.


%package tests
Summary:    Qt based library for still image metadata manipulation - unit tests
Requires:   %{name} = %{version}-%{release}
Requires:   testrunner-lite

%description tests
A Qt based library which can access and edit Exif, XMP and IPTC
metadata for still images (currently only JPEG format), offering
transparent reconciliation between different metadata representations.

This package includes the unit tests.


%package devel
Summary:    Qt based library for still image metadata manipulation - development headers
Requires:   %{name} = %{version}-%{release}

%description devel
A Qt based library which can access and edit Exif, XMP and IPTC
metadata for still images (currently only JPEG format), offering
transparent reconciliation between different metadata representations.

This package includes the development headers.


%prep
%setup -q -n %{name}-%{version}

%build
%qmake5 "VERSION=%{version}"
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%qmake_install

%fdupes  %{buildroot}/%{_libdir}/

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%license LICENSE.LGPLv21
%{_libdir}/libquillmetadata-qt5.so.*

%files tests
%defattr(-,root,root,-)
/opt/tests/libquillmetadata-qt5/

%files devel
%defattr(-,root,root,-)
%{_includedir}/qt5/quillmetadata-qt5/*
%{_libdir}/libquillmetadata-qt5.so
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.pc

